"""
This script generates a C header file containing audio values sourced from a folder of MP3 files.
Each MP3 file becomes its own 8-bit array in the header file.
Audio samples are low-pass filtered and trimmed for silence.
"""

import librosa
import pathlib
import numpy as np
import sounddevice as sd
import matplotlib.pyplot as plt

import scipy.signal


def play_all(ys: np.ndarray, sample_rate: int, blocking: bool = True):
    ys = ys.astype(np.float32)
    ys = ys / max(ys) - .5
    sd.default.samplerate = sample_rate
    sd.play(ys, blocking=blocking)


def get_code(ys: np.ndarray, name: str = None, samples_per_line: int = 20):
    name = str(name).upper()
    text = f"const uint8_t AUDIO_SAMPLES_{name}[] PROGMEM = " + "{\n  "
    for i in range(len(ys)):
        text += str(ys[i]).rjust(4)+","
        if i == len(ys) - 1:
            break
        if i % samples_per_line == samples_per_line-1:
            text += "\n  "
    text += "\n};\n\n"
    return text


def get_resampled_quantized(mp3_path: pathlib.Path, new_sample_rate: int):
    ys, sample_rate = librosa.load(mp3_path)

    # lowpass filter
    b, a = scipy.signal.butter(6, new_sample_rate / 2, fs=sample_rate,
                               btype='low', analog=False)
    ys = scipy.signal.lfilter(b, a, ys)

    # resample
    xs_new = np.arange(len(ys)) / new_sample_rate
    xs = np.arange(len(ys)) / sample_rate
    ys = np.interp(xs_new, xs, ys)

    # scale [0, 255]
    ys = ys / max(abs(min(ys)), abs(max(ys)))
    ys = ys / 2 + .5
    ys = ys * 255
    assert min(ys) >= 0
    assert max(ys) <= 255

    # quantize
    ys = ys.astype(np.int16)

    # trim zeros
    zero_value = 127
    for i1 in range(len(ys)):
        if ys[i1] != zero_value:
            break
    for i2 in range(len(ys) - 1, 0, -1):
        if ys[i2] != zero_value:
            break
    ys = ys[i1:i2]

    # ensure accuracy
    assert min(ys) >= 0
    assert max(ys) <= 255

    return ys


def generate_header_file(source_folder: str, new_sample_rate: int = 5000):
    all_code = ""
    all_ys = []
    mp3_paths = list(pathlib.Path(source_folder).glob("*.mp3"))
    if not mp3_paths:
        raise Exception(f"no mp3 files not found in {source_folder}")
    for mp3_path in mp3_paths:
        ys = get_resampled_quantized(mp3_path, new_sample_rate)
        print(f"{mp3_path.name} ({len(ys):,} bytes)")
        all_ys = np.concatenate((all_ys, ys)).astype(np.int16)
        all_code += get_code(ys, mp3_path.stem)

    print(f"TOTAL: {len(all_ys):,} bytes")

    code = "/* This source was was generated automatically.\n"
    code += " * See generation code in https://github.com/swharden/NumberSpeaker\n"
    code += " */\n\n"
    code += "#ifndef NumberSpeakerAudio_h\n"
    code += "#define NumberSpeakerAudio_h\n\n"
    code += all_code.strip() + "\n\n"
    code += "#endif"

    path_here = pathlib.Path(__file__).parent
    path_code = path_here.joinpath("../TestSketch/NumberSpeakerAudio.h")
    pathlib.Path(path_code).write_text(code)

    play_all(all_ys, new_sample_rate, False)

    plt.plot(np.arange(len(all_ys)) / new_sample_rate, all_ys)
    plt.show()


if __name__ == "__main__":
    path_here = pathlib.Path(__file__).parent
    path_mp3s = path_here.joinpath("../NumberSets/numbers3")
    generate_header_file(path_mp3s)
