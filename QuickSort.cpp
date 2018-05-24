#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

namespace{

template <typename T>

class ILessThanGen
{
public :
    virtual ~ILessThanGen (void) {}
    virtual bool operator () (const T &, const T &) const = 0;

}; // ILessThanGen

class Pers
  {
      string   myNom;
      unsigned myAge;

    public :
      Pers (const string & Nom, unsigned Age)
          : myNom (Nom), myAge (Age) {}

      const string & getNom (void) const noexcept { return myNom; }
      unsigned getAge (void) const noexcept { return myAge; }

  private :
      ostream & display (ostream & os)  const
      {
          return os << getAge () << " - " << getNom ();

      } // display()

    public :
      friend ostream & operator << (ostream & os, const Pers & p)
      {
          return p.display (os);

      }

  }; // Pers
class TriParAgeAsc : public ILessThanGen <Pers>
{
  public :
    virtual ~TriParAgeAsc (void) noexcept {}

    virtual bool operator () (const Pers & p1, const Pers & p2)
                    const noexcept
    {
        return p1.getAge () <= p2.getAge ();

    } // operator ()

}; // TriParAgeAsc

class TriParNomDesc : public ILessThanGen <Pers>
{
  public :
    virtual ~TriParNomDesc (void) noexcept {}

    virtual bool operator () (const Pers & p1, const Pers & p2)
                    const noexcept
    {
        return p1.getNom () >= p2.getNom ();

    } // operator ()

}; // TriParNomDesc
}

template <typename T>

unsigned FonctionPartitionnement(vector<T> & tab,const unsigned & first,const unsigned & last)
{
    bool isUp = true;
    unsigned pivot = first;
    unsigned courant = last;
    int incr = -1;
    while(pivot != courant)
    {
        if((!isUp && tab[pivot] < tab[courant]) || (isUp && tab[courant] < tab[pivot]))
        {
            swap(tab[pivot], tab[courant]);
            swap(pivot, courant);
            isUp = !isUp;
            incr = -incr;
        }
        courant = courant + incr;
    }
    return pivot;
}

template <typename U>

void quickSort(vector<U> & tab,const unsigned & beg,const unsigned & end)
{
      if(beg < end)
      {
         unsigned pos = FonctionPartitionnement(tab, beg, end - 1);
         quickSort(tab, beg, pos);
         quickSort(tab, pos + 1, end);
      }
}

template <typename iter_t, typename T>

iter_t partitionnement(const iter_t & first, const iter_t & last, const ILessThanGen<T> & compare)
{
    bool isUp = true;
    iter_t pivot = first;
    iter_t courant = last;
    int incr = -1;
    while(pivot != courant)
    {
        if((!isUp && compare(*pivot, *courant)) || (isUp && compare(*courant, *pivot)))
        {
            swap(*pivot, *courant);
            swap(pivot, courant);
            isUp = !isUp;
            incr = -incr;
        }
        courant = courant + incr;
    }
    return pivot;
}

template <typename iter_t, typename T>

void quickSortV2(const iter_t & beg,const iter_t & end, const ILessThanGen<T> & compare)
{
    if(beg < end)
    {
       iter_t pos = partitionnement(beg, end - 1, compare);
       quickSortV2(beg, pos, compare);
       quickSortV2(pos + 1, end, compare);
    }
}

void functorSort (void)
{
    cout << "FunctorSort : \n";

    typedef vector <Pers> CVPers;

    CVPers vPers;

    vPers.push_back ( Pers ("Charlotte", 21));
    vPers.push_back ( Pers ("Alfred",    12));
    vPers.push_back ( Pers ("Jean",      42));
    vPers.push_back ( Pers ("Noemie",    11));
    vPers.push_back ( Pers ("Berthe",    99));
    vPers.push_back ( Pers ("Agathe",    29));
    vPers.push_back ( Pers ("Sylvain",   42));
    vPers.push_back ( Pers ("Pierre",    75));

    cout << "\nTri par age croissant\n\n";

    quickSortV2 (vPers.begin (), vPers.end (), TriParAgeAsc ());

    for (const Pers & personne : vPers)
        cout << personne << '\n';

    cout << "\nTri par nom decroissant\n\n";

    quickSortV2 (vPers.begin (), vPers.end (), TriParNomDesc ());

    for (const Pers & personne : vPers)
        cout << personne << '\n';

} // functorSort()

int main()
{
    functorSort();
}
