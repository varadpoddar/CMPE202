#include <iostream>
#include <vector>
#include <string>

#include "Key.h"
#include "Kind.h"
#include "Genre.h"
#include "Region.h"
#include "Subject.h"
#include "Attributes.h"
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
    AttributeMap pairs1 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("Life of Pi")},
        {Key::LAST,  string("Martel")},
        {Key::FIRST, string("Yann")},
        {Key::YEAR,  2003},
        {Key::GENRE, Genre::ADVENTURE}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs1)));

    AttributeMap pairs2 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("The Call of the Wild")},
        {Key::LAST,  string("London")},
        {Key::FIRST, string("Jack")},
        {Key::YEAR,  1903},
        {Key::GENRE, Genre::ADVENTURE}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs2)));

    AttributeMap pairs3 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("To Kill a Mockingbird")},
        {Key::LAST,  string("Lee")},
        {Key::FIRST, string("Harper")},
        {Key::YEAR,  1960},
        {Key::GENRE, Genre::CLASSICS}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs3)));

    AttributeMap pairs4 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("Little Women")},
        {Key::LAST,  string("Alcott")},
        {Key::FIRST, string("Louisa")},
        {Key::YEAR,  1868},
        {Key::GENRE, Genre::CLASSICS}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs4)));

    AttributeMap pairs5 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("The Adventures of Sherlock Holmes")},
        {Key::LAST,  string("Doyle")},
        {Key::FIRST, string("Conan")},
        {Key::YEAR,  1892},
        {Key::GENRE, Genre::DETECTIVE}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs5)));

    AttributeMap pairs6 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("And Then There Were None")},
        {Key::LAST,  string("Christie")},
        {Key::FIRST, string("Agatha")},
        {Key::YEAR,  1939},
        {Key::GENRE, Genre::DETECTIVE}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs6)));

    AttributeMap pairs7 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("Carrie")},
        {Key::LAST,  string("King")},
        {Key::FIRST, string("Stephen")},
        {Key::YEAR,  1974},
        {Key::GENRE, Genre::HORROR}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs7)));

    AttributeMap pairs8 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("It: A Novel")},
        {Key::LAST,  string("King")},
        {Key::FIRST, string("Stephen")},
        {Key::YEAR,  1986},
        {Key::GENRE, Genre::HORROR}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs8)));

    AttributeMap pairs9 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("Frankenstein")},
        {Key::LAST,  string("Shelley")},
        {Key::FIRST, string("Mary")},
        {Key::YEAR,  1818},
        {Key::GENRE, Genre::HORROR}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs9)));

    AttributeMap pairs10 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("2001: A Space Odyssey")},
        {Key::LAST,  string("Clarke")},
        {Key::FIRST, string("Arthur")},
        {Key::YEAR,  1968},
        {Key::GENRE, Genre::SCIFI}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs10)));

    AttributeMap pairs11 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("Ender's Game")},
        {Key::LAST,  string("Card")},
        {Key::FIRST, string("Orson")},
        {Key::YEAR,  1985},
        {Key::GENRE, Genre::SCIFI}
    };
    catalogue.add(new Attributes(new AttributeMap(pairs11)));

    AttributeMap pairsA =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("The Wok of Life")},
        {Key::LAST,  string("Leung")},
        {Key::FIRST, string("Bill")},
        {Key::REGION, Region::CHINA}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsA)));

    AttributeMap pairsB =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("Chinese Cooking for Dummies")},
        {Key::LAST,  string("Yan")},
        {Key::FIRST, string("Martin")},
        {Key::REGION, Region::CHINA}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsB)));

    AttributeMap pairsC =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("Mastering the Art of French Cooking")},
        {Key::LAST,  string("Child")},
        {Key::FIRST, string("Julia")},
        {Key::REGION, Region::FRANCE}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsC)));

    AttributeMap pairsD =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("Vegetarian India")},
        {Key::LAST,  string("Jaffrey")},
        {Key::FIRST, string("Madhur")},
        {Key::REGION, Region::INDIA}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsD)));

    AttributeMap pairsE =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("Made in India")},
        {Key::LAST,  string("Sodha")},
        {Key::FIRST, string("Meera")},
        {Key::REGION, Region::INDIA}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsE)));

    AttributeMap pairsF =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("Essentials of Classic Italian Cooking")},
        {Key::LAST,  string("Hazan")},
        {Key::FIRST, string("Marcella")},
        {Key::REGION, Region::ITALY}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsF)));

    AttributeMap pairsG =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("The Complete Italian Cookbook")},
        {Key::LAST,  string("Mazzocco")},
        {Key::FIRST, string("Manuela")},
        {Key::REGION, Region::ITALY}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsG)));

    AttributeMap pairsH =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("Food for Life")},
        {Key::LAST,  string("Batmanglij")},
        {Key::FIRST, string("Najmieh")},
        {Key::REGION, Region::PERSIA}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsH)));

    AttributeMap pairsI =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("The New Orleans Kitchen")},
        {Key::LAST,  string("Devillier")},
        {Key::FIRST, string("Justin")},
        {Key::REGION, Region::US}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsI)));

    AttributeMap pairsJ =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::TITLE, string("Rodney Scott's World of BBQ")},
        {Key::LAST,  string("Scott")},
        {Key::FIRST, string("Rodney")},
        {Key::REGION, Region::US}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsJ)));

    AttributeMap pairsX =
    {
        {Key::KIND,  Kind::HOWTO},
        {Key::TITLE, string("On Writing: A Memoir of the Craft")},
        {Key::LAST,  string("King")},
        {Key::FIRST, string("Stephen")},
        {Key::SUBJECT, Subject::WRITING}
    };
    catalogue.add(new Attributes(new AttributeMap(pairsX)));
}

void search(const Catalogue& catalogue,
            const Attributes& target_attrs)
{
    cout << endl << "Find " << target_attrs << endl;

    vector<Book *> matches = catalogue.find(target_attrs);

    if (matches.size() == 0) cout << "No matches." << endl;
    else
    {
        cout << "Matches:" << endl;

        for (Book *book : matches)
        {
            cout << "  " << *book << endl;
        }
    }
}

void test(const Catalogue& catalogue)
{
    AttributeMap target_pairs1 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("Life of Pi")},
        {Key::LAST,  string("Martel")},
        {Key::FIRST, string("Yann")},
        {Key::YEAR,  2003},
        {Key::GENRE, Genre::ADVENTURE}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairs1)));

    AttributeMap target_pairs2 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::LAST,  string("KING")},
        {Key::GENRE, Genre::HORROR}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairs2)));

    AttributeMap target_pairs3 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::TITLE, string("1984")},
        {Key::LAST,  string("Orwell")},
        {Key::FIRST, string("George")},
        {Key::GENRE, Genre::CLASSICS}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairs3)));

    AttributeMap target_pairs4 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::YEAR,  1960},
        {Key::GENRE, Genre::ROMANCE}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairs4)));

    AttributeMap target_pairs5 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::YEAR,  1960}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairs5)));

    AttributeMap target_pairs6 =
    {
        {Key::KIND,  Kind::FICTION},
        {Key::GENRE, Genre::SCIFI}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairs6)));

    AttributeMap target_pairs7 =
    {
        {Key::KIND,  Kind::FICTION}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairs7)));

    AttributeMap target_pairsA =
    {
        {Key::KIND,   Kind::COOKBOOK},
        {Key::TITLE,  string("Mastering the Art of French Cooking")},
        {Key::LAST,   string("Child")},
        {Key::FIRST,  string("Julia")},
        {Key::REGION, Region::FRANCE}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairsA)));

    AttributeMap target_pairsB =
    {
        {Key::REGION, Region::CHINA}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairsB)));

    AttributeMap target_pairsC =
    {
        {Key::KIND,   Kind::COOKBOOK},
        {Key::LAST,   string("Leung")},
        {Key::REGION, Region::MEXICO}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairsC)));

    AttributeMap target_pairsD =
    {
        {Key::KIND,  Kind::COOKBOOK},
        {Key::LAST,  string("Scott")},
        {Key::FIRST, string("Rodney")}
    };
    search(catalogue, Attributes(new AttributeMap(target_pairsD)));

    AttributeMap target_pairsE =
    {
        {Key::LAST, string("King")},
    };
    search(catalogue, Attributes(new AttributeMap(target_pairsE)));
}
