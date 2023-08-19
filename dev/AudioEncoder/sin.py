import numpy as np
count = 20
xs = np.linspace(0, np.pi*2, count+1)[:count]
ys = np.sin(xs)/2+.5
ys = [str(int(x*255)) for x in ys]
print(", ".join(ys))
