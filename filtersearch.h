#ifndef FILTERSEARCH_H
#define FILTERSEARCH_H

#include "recipe.h"

class FilterSearch
{
protected:
    QVector<Recipe*> *recipes;

    static QVector<Recipe*> *arrToVectorPtr(Recipe* arr[], int arrSize);

public:
    FilterSearch(QVector<Recipe*> *recipes);

    virtual QVector<Recipe*> * search() = 0;
};

template <typename T>
class SingleSearch : public FilterSearch
{
private:
    T limit;
    QVector<T> vector;

public:
    SingleSearch(T value, QVector<T> &vector, QVector<Recipe*> *recipes);

    virtual QVector<Recipe*> * search();
};

class CombinedSearch : public FilterSearch
{
private:
    double calLimit;
    int timeLimit;
    QString cuisineName;

public:
    CombinedSearch(QVector<Recipe*> *recipeList, QString cuisine, double climit, int tlimit);

    virtual QVector<Recipe*> * search();
};

#endif // FILTERSEARCH_H
