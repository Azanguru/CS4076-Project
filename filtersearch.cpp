#include "filtersearch.h"

FilterSearch::FilterSearch(QVector<Recipe *> *recipes)
{
    this->recipes = recipes;
}

template <typename T>
SingleSearch<T>::SingleSearch(T value, QVector<T> &vector, QVector<Recipe*> *recipes)
    : FilterSearch(recipes)
{
    this->limit = value;
    this->vector = vector;
}

template <typename T>
QVector<Recipe*> * SingleSearch<T>::search()
{
    int size = vector.size();
    QVector<Recipe*> *result = new QVector<Recipe*>;

    for (int i = 0; i < size; i++)
    {
        if (vector.at(i) <= limit)
        {
            result->append(recipes->at(i));
        }
    }

    return result;
}

CombinedSearch::CombinedSearch(QVector<Recipe*> *recipeList, QString cuisine, double climit, int tlimit)
    : FilterSearch(recipeList)
{
    cuisineName = cuisine;
    if (climit == 0.0) { calLimit = 100000.0; }
    else { calLimit = climit; }
    if (tlimit == 0) { timeLimit = 300; }
    else { timeLimit = tlimit; }
}

QVector<Recipe*> * CombinedSearch::search()
{
    int size = recipes->size();
    QVector<Recipe*> *result = new QVector<Recipe*>;

    for (int i = 0; i < size; i++)
    {
        if (cuisineName == "")
        {
            if ((timeLimit >= recipes->at(i)->getTime()) && (calLimit >= recipes->at(i)->getTotalCalories()))
            {
                result->append(recipes->at(i));
            }

        } else {
            if ((recipes->at(i)->getCuisine() == cuisineName) && (timeLimit >= recipes->at(i)->getTime())
                    && (calLimit >= recipes->at(i)->getTotalCalories()))
            {
                result->append(recipes->at(i));
            }
        }
    }

    return result;
}

template class SingleSearch<double>;
template class SingleSearch<int>;
