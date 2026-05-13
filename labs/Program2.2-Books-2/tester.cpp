#include <iostream>
#include <vector>
#include <string>

#include "Book.h"
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
    catalogue.add(new Attributes("Life of Pi", "Martel", "Yann",
                                 2003, Genre::ADVENTURE));
    catalogue.add(new Attributes("The Call of the Wild",
                                 "London", "Jack",
                                 1903, Genre::ADVENTURE));

    catalogue.add(new Attributes("To Kill a Mockingbird",
                                 "Lee", "Harper",
                                 1960, Genre::CLASSICS));
    catalogue.add(new Attributes("Little Women", "Alcott", "Louisa",
                                 1868, Genre::CLASSICS));

    catalogue.add(new Attributes(
                            "The Adventures of Sherlock Holmes",
                            "Doyle", "Conan",
                            1892, Genre::DETECTIVE));
    catalogue.add(new Attributes("And Then There Were None",
                                 "Christie", "Agatha",
                                 1939, Genre::DETECTIVE));

    catalogue.add(new Attributes("Carrie", "King", "Stephen",
                                 1974, Genre::HORROR));
    catalogue.add(new Attributes("It: A Novel", "King", "Stephen",
                                 1986, Genre::HORROR));
    catalogue.add(new Attributes("Frankenstein", "Shelley", "Mary",
                                 1818, Genre::HORROR));

    catalogue.add(new Attributes("2001: A Space Odyssey",
                                 "Clarke", "Arthur",
                                 1968, Genre::SCIFI));
    catalogue.add(new Attributes("Ender's Game", "Card", "Orson",
                                 1985, Genre::SCIFI));
}

void search(const Catalogue& catalogue,
            const Attributes &target_attrs)
{
    cout << endl << "Find " << target_attrs << endl;

    vector<Book *> matches = catalogue.find(target_attrs);

    if (matches.size() == 0) cout << "No matches." << endl;
    else
    {
        cout << "Matches:" << endl;

        for (Book *book : matches)
        {
            cout << "  " << *book->get_attributes() << endl;
        }
    }
}

void test(const Catalogue& catalogue)
{
    Attributes target_attrs1("Life of Pi", "Martel", "Yann",
                             2003, Genre::ADVENTURE);
    search(catalogue, target_attrs1);

    Attributes target_attrs2("", "King", "", 0, Genre::HORROR);
    search(catalogue, target_attrs2);

    Attributes target_attrs3("1984", "Orwell", "George",
                             0, Genre::CLASSICS);
    search(catalogue, target_attrs3);

    Attributes target_attrs4("", "", "", 1960, Genre::ROMANCE);
    search(catalogue, target_attrs4);

    Attributes target_attrs5("", "", "", 1960, Genre::UNSPECIFIED);
    search(catalogue, target_attrs5);

    Attributes target_attrs6("", "", "", 0, Genre::SCIFI);
    search(catalogue, target_attrs6);

    Attributes target_attrs7("", "", "", 0, Genre::UNSPECIFIED);
    search(catalogue, target_attrs7);
}
