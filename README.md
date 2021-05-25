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

## Keleto funkcijų testavimas

Kaip jau buvo galima suprasti iš pirmųjų testų, push_back() veikia taip, kaip turėtų.

### Operatoriai

Tikrinti visi lyginimo operatoriai:
```shell
bool operator==(Vector<T> &v);
bool operator!=(Vector<T> &v);
bool operator<(Vector<T> &v);
bool operator<=(Vector<T> &v);
bool operator>(Vector<T> &v);
bool operator>=(Vector<T> &v);
```

Buvo žiūrima, kad atsakymai sutaptų su tokiais, kuriuos gautume naudojant std::vector:
```shell
Vector<int> a = { 0, 1, 2 };
Vector<int> b = { 0, 1, 2 };
Vector<int> c = { 1, 2 };

cout<<"a == b: "<<(a==b)<<endl;
cout<<"a == c: "<<(a==c)<<endl;
cout<<"a != b: "<<(a!=b)<<endl;
cout<<"a != c: "<<(a!=c)<<endl;
cout<<"a < b: "<<(a<b)<<endl;
cout<<"a < c: "<<(a<c)<<endl;
cout<<"a <= b: "<<(a<=b)<<endl;
cout<<"a <= c: "<<(a<=c)<<endl;
cout<<"a > b: "<<(a>b)<<endl;
cout<<"a > c: "<<(a>c)<<endl;
cout<<"a >= b: "<<(a>=b)<<endl;
cout<<"a >= c: "<<(a>=c)<<endl;
```
Gauti atsakymai, kaip matome, yra tokie, kokie turi būti:
```shell
a == b: 1
a == c: 0
a != b: 0
a != c: 1
a < b: 0
a < c: 1
a <= b: 1
a <= c: 1
a > b: 0
a > c: 0
a >= b: 1
a >= c: 0
```

### at()

Grąžina kurį nors elementą, priklausomai nuo indekso (jei indeksas už ribų - turi mesti exception'ą):
```shell
reference at(size_type i);
```
Testuosime su tuo pačiu konteineriu a:
```shell
Vector<int> a = { 0, 1, 2 };
cout<<"0 elementas: "<<a.at(0)<<endl;
cout<<"1 elementas: "<<a.at(1)<<endl;
cout<<"2 elementas: "<<a.at(2)<<endl;
cout<<"3 elementas: "<<a.at(3)<<endl;
```
Kaip matome, turėtų išmesti exception'ą, kai bandys pasiekti 3 elementą:
```shell
0 elementas: 0
1 elementas: 1
2 elementas: 2
3 elementas: terminate called after throwing an instance of 'std::out_of_range'
  what():  Index(Vector::at) out of range!
```
Valio! Viskas veikia teisingai.

### size()

Grąžina konteinerio dydį:
```shell
size_type size() const { return avail - data; }
```
Testuosime su tuo pačiu konteineriu a:
```shell
Vector<int> a = { 0, 1, 2 };
cout<<"a size: "<<a.size()<<endl;
```
Kaip matome žemiau, gauname 3:
```shell
a size: 3
```
