#include <iostream>
using namespace std;

int main()
{
    int v[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int o[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int l[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int f[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int t[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int m[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int r[10]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int volvo, fiat, motor;
    //long int skaits=0;
    //int skaits2=0;
    cout << "volvo + fiat = motor" << endl;
    for (int g=0; g<10;g++)
    {

        for (int j=0; j<10; j++)
        {
            if (v[g]==o[j]) continue;
            for (int w=0; w<10; w++)
            {
                if (v[g]==f[w] || o[j]==f[w]) continue;
                for (int z=0; z<10; z++)
                {
                    if (v[g]==i[z]||o[j]==i[z]||f[w]==i[z]) continue;
                    for (int x=0; x<10; x++)
                    {
                        if(v[g]==m[x] || o[j]==m[x] || i[z]==m[x] || f[w]==m[x]) continue;//skaits2++;
                        for (int s=0; s<10; s++)
                        {
                            if (v[g]==l[s] || o[j]==l[s] || i[z]==l[s] || f[w]==l[s] || m[x]==l[s]) continue;
                            for (int n=0; n<10; n++)
                            {
                                if (v[g]==a[n] || o[j]==a[n] || i[z]==a[n] || f[w]==a[n] || m[x]==a[n] || l[s]==a[n]) continue;
                                for (int y=0; y<10; y++)
                                {
                                    if (v[g]==t[y] || o[j]==t[y] || i[z]==t[y] || f[w]==t[y] || m[x]==t[y] || l[s]==t[y] || a[n]==t[y]) continue;
                                    for (int b=0; b<10; b++)
                                    {
                                        if (r[b]==o[j] || v[g]==r[b] || r[b]==i[z] || r[b]==f[w] || m[x]==r[b] || l[s]==r[b] || a[n]==r[b] || r[b]==t[y] ) continue;
                                        //skaits++;
                                        volvo=v[g]*10000+o[j]*1000+l[s]*100+v[g]*10+o[j];
                                        fiat=f[w]*1000+i[z]*100+a[n]*10+t[y];
                                        motor=m[x]*10000+o[j]*1000+t[y]*100+o[j]*10+r[b];
                                        if (volvo+fiat==motor) cout << volvo << " + "<< fiat << " = " << motor <<endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
