$ phi(n) = n product_(i = 1)^k (1 - 1/p_i). $

两条常用性质：它是积性的，即 $gcd(a, b) = 1$ 时 $phi(a b) = phi(a) phi(b)$；并且 $sum_(d ∣ n) phi(d) = n$，也即 $phi(n) = sum_(d ∣ n) mu(d) n/d$。

欧拉定理：$gcd(a, m) = 1$ 时 $a^(phi(m)) equiv 1 (mod m)$。竞赛里更常用的是扩展欧拉定理，它给指数降幂——$b >= phi(m)$ 时对任意 $a$ 都有
$ a^b equiv a^(b mod phi(m) + phi(m)) (mod m). $

线性筛求 $phi$ 的递推：素数的 $phi(p) = p - 1$；对 $i dot p$，若 $p ∣ i$ 则 $phi(i p) = p phi(i)$，否则 $phi(i p) = (p - 1) phi(i)$。见下面的 `sieve()`；只求单个数用 `Phi()`，复杂度 $O(sqrt(n))$。
