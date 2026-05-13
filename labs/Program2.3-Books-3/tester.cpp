#include <iostream>
#include <vector>
#include <string>

#include "Book.h"
#include "Fiction.h"
#include "FictionAttrs.h"
#include "Cookbook.h"
#include "CookbookAttrs.h"
#include "Catalogue.h"

void fill(Catalogue& catalogue);
void test(const Catalogue& catalogue);

int main()
{
    Catalogue catalogue;
    fill(catalogue);
    test(catalogue);

    return 0;
}

void fill(Catalogue& catalogue)
{
    catalogue.add(new FictionAttrs("Life of Pi", "Martel", "Yann",
                                   2003, Genre::ADVENTURE));
    catalogue.add(new FictionAttrs("The Call of the Wild",
                                   "London", "Jack",
                                   1903, Genre::ADVENTURE));

    catalogue.add(new FictionAttrs("To Kill a Mockingbird",
                                   "Lee", "Harper",
                                   1960, Genre::CLASSICS));
    catalogue.add(new FictionAttrs("Little Women",
                                   "Alcott", "Louisa",
                                   1868, Genre::CLASSICS));

    catalogue.add(new FictionAttrs(
                            "The Adventures of Sherlock Holmes",
                            "Doyle", "Conan",
                            1892, Genre::DETECTIVE));
    catalogue.add(new FictionAttrs("And Then There Were None",
                                   "Christie", "Agatha",
                                   1939, Genre::DETECTIVE));

    catalogue.add(new FictionAttrs("Carrie", "King", "Stephen",
                                   1974, Genre::HORROR));
    catalogue.add(new FictionAttrs("It: A Novel", "King", "Stephen",
                                   1986, Genre::HORROR));
    catalogue.add(new FictionAttrs("Frankenstein",
                                   "Shelley", "Mary",
                                   1818, Genre::HORROR));

    catalogue.add(new FictionAttrs("2001: A Space Odyssey",
                                   "Clarke", "Arthur",
                                   1968, Genre::SCIFI));
    catalogue.add(new FictionAttrs("Ender's Game", "Card", "Orson",
                                   1985, Genre::SCIFI));

    catalogue.add(new CookbookAttrs("The Woks of Life",
                                    "Leung", "Bill", Region::CHINA));
    catalogue.add(new CookbookAttrs("Chinese Cooking for Dummies",
                                    "Yan", "Martin", Region::CHINA));

    catalogue.add(new CookbookAttrs(
                            "Mastering the Art of French Cooking",
                            "Child", "Julia", Region::FRANCE));

    catalogue.add(new CookbookAttrs("Vegetarian India",
                                    "Jaffrey", "Madhur",
                                    Region::INDIA));
    catalogue.add(new CookbookAttrs("Made in India",
                                    "Sodha", "Meera",
                                    Region::INDIA));

    catalogue.add(new CookbookAttrs(
                            "Essentials of Classic Italian Cooking",
                            "Hazan", "Marcella", Region::ITALY));
    catalogue.add(new CookbookAttrs(
                            "The Complete Italian Cookbook",
                            "Mazzocco", "Manuela", Region::ITALY));

    catalogue.add(new CookbookAttrs("The Mexican Home Kitchen",
                                    "Martinez", "Mely",
                                    Region::MEXICO));

    catalogue.add(new CookbookAttrs("The New Orleans Kitchen",
                                    "Devillier", "Justin",
                                    Region::US));
    catalogue.add(new CookbookAttrs("Rodney Scott's World of BBQ",
                                    "Scott", "Rodney",
                                    Region::US));
}

void search_fiction(const Catalogue& catalogue,
                    const FictionAttrs& target_attrs)
{
    cout << endl << "Find " << target_attrs << endl;

    vector<Fiction *> matches = catalogue.find(target_attrs);

    if (matches.size() == 0) cout << "No matches." << endl;
    else
    {
        cout << "Matches:" << endl;

        for (Fiction *book : matches)
        {
            FictionAttrs *attrs = dynamic_cast<FictionAttrs *>(book->get_attributes());
            cout << "  " << *attrs << endl;
        }
    }
}

void search_cookbook(const Catalogue& catalogue,
                     const CookbookAttrs& target_attrs)
{
    cout << endl << "Find " << target_attrs << endl;

    vector<Cookbook *> matches = catalogue.find(target_attrs);

    if (matches.size() == 0) cout << "No matches." << endl;
    else
    {
        cout << "Matches:" << endl;

        for (Cookbook *book : matches)
        {
            CookbookAttrs *attrs = dynamic_cast<CookbookAttrs *>(book->get_attributes());
            cout << "  " << *attrs << endl;
        }
    }
}

void test(const Catalogue& catalogue)
{
    FictionAttrs target_attrs1("Life of Pi", "Martel", "Yann",
                               2003, Genre::ADVENTURE);
    search_fiction(catalogue, target_attrs1);

    FictionAttrs target_attrs2("", "King", "", 0, Genre::HORROR);
    search_fiction(catalogue, target_attrs2);

    FictionAttrs target_attrs3("1984", "Orwell", "George", 0, Genre::CLASSICS);
    search_fiction(catalogue, target_attrs3);

    FictionAttrs target_attrs4("", "", "", 1960, Genre::ROMANCE);
    search_fiction(catalogue, target_attrs4);

    FictionAttrs target_attrs5("", "", "", 1960, Genre::UNSPECIFIED);
    search_fiction(catalogue, target_attrs5);

    FictionAttrs target_attrs6("", "", "", 0, Genre::SCIFI);
    search_fiction(catalogue, target_attrs6);

    FictionAttrs target_attrs7("", "", "", 0, Genre::UNSPECIFIED);
    search_fiction(catalogue, target_attrs7);

    CookbookAttrs target_attrsA("Mastering the Art of French Cooking",
                                "Child", "Julia", Region::FRANCE);
    search_cookbook(catalogue, target_attrsA);

    CookbookAttrs target_attrsB("", "", "", Region::CHINA);
    search_cookbook(catalogue, target_attrsB);

    CookbookAttrs target_attrsC("", "Hom", "", Region::MEXICO);
    search_cookbook(catalogue, target_attrsC);

    CookbookAttrs target_attrsD("", "Scott", "Rodney", Region::UNSPECIFIED);
    search_cookbook(catalogue, target_attrsD);
}
