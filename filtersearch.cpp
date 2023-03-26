#include "filtersearch.h"

FilterSearch::FilterSearch(QVector<Recipe *> *recipes)
{
    this->recipes = recipes;
}

QVector<Recipe*> FilterSearch::arrToVector(Recipe *arr[], int arrSize)
{
    QVector<Recipe*> vector;
    for (int i = 0; i < arrSize; i++)
    {
        if (!(arr[i] == nullptr))
        {
            vector.append(arr[i]);
        } else {
            i = arrSize;
        }
    }
    return vector;
}

template <typename T>
SingleSearch<T>::SingleSearch(T value, T arr[], int arrSize, QVector<Recipe*> *recipes)
    : FilterSearch::FilterSearch(recipes)
{
    this->value = value;
    this->arr = arr;
    this->arrSize = arrSize;
}

template <typename T>
QVector<Recipe*> SingleSearch<T>::search()
{
    int counter = 0;
    Recipe* recipeArr[arrSize];

    for (int i = 0; i < arrSize; i++)
    {
        if (value >= arr[i])
        {
            recipeArr[counter] = recipes->at(i);
            counter++;
        }
    }

    return arrToVector(recipeArr, arrSize);
}

template <typename T>
bool SingleSearch<T>::operator>=(QString const& obj1)
{
    return  obj1 == value;
}

CombinedSearch::CombinedSearch(QVector<Recipe*> *recipeList, QString cuisine = "", double limit1 = 10000, int limit2 = 10000)
    : FilterSearch::FilterSearch(recipeList)
{
    cuisineName = cuisine;
    calLimit = limit1;
    timeLimit = limit2;
}

QVector<Recipe*> CombinedSearch::search()
{
    int size = recipes->size();
    int counter = 0;
    Recipe* arr[size];

    for (int i = 0; i < size; i++)
    {
        if (cuisineName.isNull())
        {
            if ((recipes->at(i)->getCuisine() == cuisineName) && (timeLimit >= recipes->at(i)->getTime()) && (calLimit >= recipes->at(i)->getTime()))
            {
                arr[counter] = recipes->at(i);
                counter++;
            }
        } else {
            if ((timeLimit >= recipes->at(i)->getTime()) && (calLimit >= recipes->at(i)->getTime()))
            {
                arr[counter] = recipes->at(i);
                counter++;
            }
        }
    }

    return arrToVector(arr, size);
}
