### `generateUniqueID` - Justification

On the whole, the **probability of collision** of the same `ID`s generated by the `generateUniqueID()` **function** depends on the number of `ID`s that are generated and the range of the random number generated by the `Math.random()` function.

In this case, the `Math.random()` **function** generates a random number from the range $\{1, 1000\}$, and this random number is used to divide the **current timestamp** (in milliseconds) generated by `Date.now()`. The result is then *rounded down* to obtain the **unique** `ID`.

**Assumptions:**

- The timestamp value returned by `Date.now()` changes every millisecond.
- The `Math.random()` **function** generates a uniformly distributed random number from the range $\{1, 1000\}$.

### Analysis

For each **unique** `ID` generated, there exist $1000$ possible values for the random number generated by `Math.random()`, resulting in $1000$ possible values for the timestamp divided by the random number. Since the timestamp value changes every **millisecond**, this means that we can generate at most $1000$ unique `ID`s per millisecond.

Suppose we generate $n$ **unique** `ID`s in $m$ milliseconds. Since there are $1000$ possible values for the random number generated by `Math.random()`, we can have at most $1000 \times m$ **unique** `ID`s generated in $m$ milliseconds. To express the number of possible combinations of choosing $n$ **unique** `ID`s from $1000 \times m$ **unique** `ID`s, we use the following formula: $\text{C}{1000 \times m \choose n}$. Therefore, the probability of collision is given by: 

> TODO: provide the final formula in the $\LaTeX$ format.

Observe that as $n$ grows, so does the probability of collision. This is because the probability of uniqueness decreases as $n$ increases. However, the probability of collision is still relatively low, even for large values of $n$.

### Justification

Indeed, the value returned by `Date.now()` would depend on the system clock (and an array of other factors), which shall lower the probability of collision. Furthermore, our system is never expected to generate such a large number of `ID`s in a short period of time, so the probability of collision is acceptable for our use case. Therefore, we can conclude that the `generateUniqueID()` **function** is suitable for our system. Still, the function is labeled as _'pseudo'_ unique because of the aforementioned reasons.