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

### Testavimas su v2.0

Vėliau pabandžiau naudoti šį Vector su jau turima Studentų Pažymių programa (v2.0). Viskas veikė teisingai, tad atlikau porą spartos testų:

#### Su 100000 studentų

| Konteineris    | Nuskaitymas   | Rūšiavimas   | Išvedimas      | **Galutinis laikas** |
| :------------- | :------------ | :----------- | :------------- | :------------------- |
| Vector         | 0.60065       | 0.14792      | 0.26582        | 1.01841              |
| std::vector    | 0.59477       | 0.14890      | 0.27523        | 1.02939              |

#### Su 1000000 studentų

| Konteineris    | Nuskaitymas   | Rūšiavimas   | Išvedimas      | **Galutinis laikas** |
| :------------- | :------------ | :----------- | :------------- | :------------------- |
| Vector         | 5.00921       | 1.65506      | 1.63270        | 9.29882              |
| std::vector    | 5.02914       | 1.70405      | 1.69789        | 9.43689              |

## Keleto funkcijų testavimas

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

### begin()

Grąžina pradžios iteratorių:
```shell
iterator begin() noexcept { return data; }
```
Testuosime su tuo pačiu konteineriu a:
```shell
Vector<int> a = { 0, 1, 2 };
cout<<"a.begin() ir elementai po to: "<<*(a.begin())<<*(a.begin()+1)<<*(a.begin()+2)<<endl;
```
Taigi, gauname tai, ką ir turėjome gauti - "012":
```shell
a.begin() ir elementai po to: 012
```

### push_back()

Kaip jau buvo galima suprasti iš pirmųjų testų, push_back() veikia taip, kaip turėtų, bet vis tiek galima pavaizduoti testavimą.

Pridedamas naujas elementas po paskutinio inicializuoto elemento:
```shell
void push_back(const T& val);
```
Testuosime su tuo pačiu konteineriu a:
```shell
Vector<int> a = { 0, 1, 2 };
a.push_back(4);
a.push_back(6);
for (int i = 0; i<a.size(); i++)
{
    cout<<"a "<<i<<" elementas: "<<a[i]<<endl;
}
```
Gautas atsakymas:
```shell
a 0 elementas: 0
a 1 elementas: 1
a 2 elementas: 2
a 3 elementas: 4
a 4 elementas: 6
```
