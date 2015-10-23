#include "searchbox.h"

#include "gsuggestcompletion.h"

SearchBox::SearchBox(QWidget *parent)
    : QLineEdit(parent)
{
    setWindowTitle("Search with Google");

    completer = new GSuggestCompletion(this);

    adjustSize();
    setFocus();
}

SearchBox::~SearchBox()
{

}

void SearchBox::doSearch()
{

}
