# Intro to Crypto 2

Similar to the previous challenge, we are given a public key (pubkey.pem) and a message encrypted with this key (message.txt).

## Solution

Looking at the challenge description may indicate what the problem here is:
`I learned my lesson from the mistakes made in the last challenge! Now p and q are huge, I promise!`

While searching for RSA related CTF tasks, I found this repository: https://github.com/Ganapati/RsaCtfTool, that despite me not getting it to work properly, includes a cool list of possbile attacks against RSA:
```
Prime N detection
Weak public key factorization
Wiener's attack
Hastad's attack (Small public exponent attack)
Small q (q < 100,000)
Common factor between ciphertext and modulus attack
Fermat's factorisation for close p and q
Gimmicky Primes method
Past CTF Primes method
Self-Initializing Quadratic Sieve (SIQS) using Yafu
Common factor attacks across multiple keys
Small fractions method when p/q is close to a small fraction
Boneh Durfee Method when the private exponent d is too small compared to the modulus (i.e d < n^0.292)
Elliptic Curve Method
Pollards p-1 for relatively smooth numbers
Mersenne primes factorization
Londahl's factorisation for close p and q
Qi Cheng's unsafe primes factorization
```

Going through this list I found that [Fermat's factorisation](https://en.wikipedia.org/wiki/Fermat%27s_factorization_method) seems to be promising and I implemented the code
found [here](https://www.johndcook.com/blog/2018/10/28/fermat-factoring/) into my program (The steps to get _N_ and _e_ are trivial and were described in the previous writeup):

```python
from sympy import sqrt, log, ceiling, Integer
from Crypto.Util.number import long_to_bytes
from Crypto.Util.number import inverse

N = 11081631875903145989449935723431993312048263659503073501368579288661507666926127398551161494057149306128113773163942639308834214121175806650609216999457699806761832905200688030797211656004392019494461369905299150414106039926917206543955359193966893148964232596310365304968051716316421386564037673515738090636958039103706945349258789436043666088184674948218539196263599899299117746103356732914111330139176914363944699056706536973601851519543254647327613986429683489937828404640743341705415177790924588759219148196121101333618974290049804819348181073769764832469557718828674823915162708288827812462173689965257895702511
e = 65537
m = int(open("message.txt", "r").read().strip())

def is_square(n):
    return type(sqrt(n)) == Integer

def fermat_factor(n):

    num_digits = int(log(n, 10).evalf() + 1)
    a = ceiling( sqrt(n).evalf(num_digits) )

    while not is_square(a * a - n):
        a += 1

    b = sqrt(a * a - n)

    return (a + b, a - b)

p, q = fermat_factor(N)
d = inverse(e, (p - 1) * (q - 1))

decrypted = pow(m, int(d), N)

print(long_to_bytes(decrypted).decode("utf-8"))
```

Flag: `CSCG{Ok,_next_time_I_choose_p_and_q_random...}`

## Mitigation

Choose two __distinct__ and large primes for _q_ and _q_. Fermat's factorization method only works if _p_ and _q_ have almost the same value.

