import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np
from matplotlib import rc

'''
The original Weierstrass function is defined as a Fourier series:
(According to https://en.wikipedia.org/wiki/Weierstrass_function)
$W_{(a,b)}(x) = \sum_{n=0}^{\infty} a^n \cos(b^n \pi x)$,
where $0 < a < 1$, $b \in 2\mathbb{Z} + 1$ and $ab > 1 + \dfrac{3}{2} \pi$.
'''

rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)

N = 1000 # Approchment of infinity
a, b = 0.82, 7 # value of the parameters a and b

def WeierstrassFunction(x):
    res = 0
    for n in range(N):
        res += np.power(a, n) * np.cos(np.power(b, n) * np.pi * x)
    return res

fig, ax = plt.subplots(figsize=(16, 10))
ln, = ax.plot(0, WeierstrassFunction(0),
              label=f'N = {N} for infinity,\n\
                    a = {a},\n\
                    b = {b}',
                    color='black')
xdata, ydata = list(), list()

def init():
    ax.set_title(r'Animation of Weierstrass function: '
                 r'$\displaystyle W_{(a,b)}(x) = \sum_{n=0}^{\infty} a^n \cos(b^n \pi x)$',
                 color='black',
                 fontsize=14)

    ax.set_xlabel(r'$x$', fontsize=12)
    ax.set_xlim(-6, 6)
    ax.set_xticks(np.linspace(-5, 5, 11))

    ax.set_ylabel(r'$W_{(a, b)}(x)$', rotation=0, fontsize=12)
    ax.set_ylim(-6, 6)
    ax.set_yticks(np.linspace(-5, 5, 11))

    plt.legend(loc='best')
    return ln,

def update(frame):
    xdata.append(frame)
    ydata.append(WeierstrassFunction(frame))
    ln.set_data((xdata, ydata))
    return ln,

def main():
    animeObj = anim.FuncAnimation(fig,
                                  update,
                                  frames=np.linspace(-5, 5, 1000),
                                  init_func=init,
                                  blit=True)
    animeObj.save('WeierstrassFunction.mp4', writer='ffmpeg', fps=30)
    plt.show()


if __name__ == "__main__":
    main()