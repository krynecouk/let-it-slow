# Let it Slow

One hundred thousand falling snowflakes.

![Teaser of the gameplay](let-it-slow.gif)

Application was programmed **without** focusing on the performance of the rendering. Aim of this project is to measure and analyze performance in such an application. Obtained results will serve as a benchmark comparison with an optimized solution (TBD).

## Performance

As performance indicators were measured CPU cache misses and branche mispredictions from three different implementations. Each of them differes in used data type for stored snowflakes:

- `vector`
- `vector` modified
- `list`

For cache and branch profiling was used [Cachegrind](https://valgrind.org/docs/manual/cg-manual.html).

### `std::vector`

> Elements of a `vector` are stored contiguously in a memory and therefore most suitable for CPU caches [Drepper, 2007]. Best cache miss results. But bad branch prediction results because of the unpredicted `if` in the [Game](./src/Game.cpp)::`update` function. Definitely place for an improvement.

```
I   refs:      11,380,565,597
I1  misses:         1,720,676
LLi misses:           531,879
I1  miss rate:           0.02%
LLi miss rate:           0.00%

D   refs:       6,235,673,352  (4,171,929,516 rd   + 2,063,743,836 wr)
D1  misses:        33,433,992  (   27,942,476 rd   +     5,491,516 wr)
LLd misses:        31,596,451  (   26,499,864 rd   +     5,096,587 wr)
D1  miss rate:            0.5% (          0.7%     +           0.3%  )
LLd miss rate:            0.5% (          0.6%     +           0.2%  )

LL refs:           35,154,668  (   29,663,152 rd   +     5,491,516 wr)
LL misses:         32,128,330  (   27,031,743 rd   +     5,096,587 wr)
LL miss rate:             0.2% (          0.2%     +           0.2%  )

Branches:       1,453,407,417  (1,260,642,758 cond +   192,764,659 ind)
Mispredicts:       31,834,170  (   13,412,868 cond +    18,421,302 ind)
Mispred rate:             2.2% (          1.1%     +           9.6%   )
```

### `std::vector` (modified)

> Every fallen snowflake was removed from the `vector` of snowflakes. Worst result because of the `O(n)` complexity of `v.erase(iterator)` and modified vector size.

```
I   refs:      217,986,584,089
I1  misses:          1,764,113
LLi misses:            257,651
I1  miss rate:            0.00%
LLi miss rate:            0.00%

D   refs:      157,450,187,541  (97,455,277,690 rd   + 59,994,909,851 wr)
D1  misses:      2,239,807,107  ( 2,234,159,053 rd   +      5,648,054 wr)
LLd misses:        236,059,097  (   231,605,745 rd   +      4,453,352 wr)
D1  miss rate:             1.4% (           2.3%     +            0.0%  )
LLd miss rate:             0.1% (           0.2%     +            0.0%  )

LL refs:         2,241,571,220  ( 2,235,923,166 rd   +      5,648,054 wr)
LL misses:         236,316,748  (   231,863,396 rd   +      4,453,352 wr)
LL miss rate:              0.1% (           0.1%     +            0.0%  )

Branches:        3,926,626,287  ( 3,733,811,844 cond +    192,814,443 ind)
Mispredicts:        11,446,855  (    11,164,516 cond +        282,339 ind)
Mispred rate:              0.3% (           0.3%     +            0.1%   )
```

### `std::list`

> Worse results compared to the `vector` with a static size. Elements of `list` are scattered across the main memory which is not CPU cache friendly. [Stroustrup, 2012]

```
I   refs:      11,650,966,650
I1  misses:         1,671,132
LLi misses:           537,711
I1  miss rate:           0.01%
LLi miss rate:           0.00%

D   refs:       6,394,292,664  (4,266,441,223 rd   + 2,127,851,441 wr)
D1  misses:        44,782,629  (   39,361,099 rd   +     5,421,530 wr)
LLd misses:        42,974,182  (   37,944,111 rd   +     5,030,071 wr)
D1  miss rate:            0.7% (          0.9%     +           0.3%  )
LLd miss rate:            0.7% (          0.9%     +           0.2%  )

LL refs:           46,453,761  (   41,032,231 rd   +     5,421,530 wr)
LL misses:         43,511,893  (   38,481,822 rd   +     5,030,071 wr)
LL miss rate:             0.2% (          0.2%     +           0.2%  )

Branches:       1,458,409,526  (1,265,186,899 cond +   193,222,627 ind)
Mispredicts:       13,694,487  (   13,405,127 cond +       289,360 ind)
Mispred rate:             0.9% (          1.1%     +           0.1%   )
```

## Sources

- [Drepper, 2007] : [What Every Programmer Should Know About Memory](https://www.akkadia.org/drepper/cpumemory.pdf)
- [Stroustrup, 2012] : [Why you should avoid Linked Lists](https://www.youtube.com/watch?v=YQs6IC-vgmo)
