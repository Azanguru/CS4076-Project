#ifndef FILTERSEARCH_H
#define FILTERSEARCH_H

#include "recipe.h"

class FilterSearch
{
protected:
    QVector<Recipe*> *recipes;

    static QVector<Recipe*> arrToVector(Recipe* arr[], int arrSize);

public:
    FilterSearch(QVector<Recipe*> *recipes);

    virtual QVector<Recipe*> search() = 0;
    QVector<Recipe*> combineSearch();
};

template <typename T>
class SingleSearch : public FilterSearch
{
private:
    T value;
    T arr[];
    int arrSize;

    bool operator>=(QString const& obj1);

public:
    SingleSearch(T value, T arr[], int arrSize, QVector<Recipe*> *recipes);

    virtual QVector<Recipe*> search();
};

class CombinedSearch : public FilterSearch
{
private:
    double calLimit;
    int timeLimit;
    QString cuisineName;

public:
    CombinedSearch(QVector<Recipe*> *recipeList, QString cuisine, double limit1, int limit2);

    virtual QVector<Recipe*> search();
};

#endif // FILTERSEARCH_H
