# VU-OP-Nr.3-Vector
Tai - savadarbė konteinerio std::vector implementacija. Kad būtų aišku, kas su kuo lyginama, mano implementacija bus vadinama "Vector", o įprastinis - "std::vector".

## Spartos testai

Iš pradžių pratestavau tiesiog push'indamas 10^n (n ∈ [4,8]) elementų į konteinerius (std::vector ir manąjį Vector):
```shell
for(int i = 0; i<n; i++)
{
    v.push_back(i);
}
```

| Konteineris    | 10000 (10^4) | 100000 (10^5) | 1000000 (10^6) | 10000000 (10^7) | 100000000 (10^8) |
| :------------- | :----------- | :------------ | :------------- | :-------------- | :--------------- |
| Vector         | 0.00099      | 0.00300       | 0.01701        | 0.18094         | 1.70736          |
| std::vector    | 0.00100      | 0.00297       | 0.01796        | 0.17092         | 1.63507          |

Galime daryti išvadą, kad std::vector yra kiek greitesnis.

Konteinerių atminties perskirstymų skaičius testavimo metu nesiskyrė:

| Konteineris    | 10000 (10^4) | 100000 (10^5) | 1000000 (10^6) | 10000000 (10^7) | 100000000 (10^8) |
| :------------- | :----------- | :------------ | :------------- | :-------------- | :--------------- |
| Vector         | 11           | 15            | 18             | 21              | 25               |
| std::vector    | 11           | 15            | 18             | 21              | 25               |

