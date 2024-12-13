
/* 
   Code by: ido jhirad	
   Project: Sorted List
   Date: 22/05/24
   Review by: oded
   Review Date: 22/05/24
   Approved by: oded
   Approval Date: 22/05/24
*/
#include <stdlib.h> /* for size_t, malloc and free */
#include <assert.h> /* for assert */
#include "dllist.h"
#include "sortedlist.h"

struct sortedlist
{
    dllist_t *list;
    sortedlist_cmp_func_t compare;
};

sortedlist_t *SortedlistCreate(sortedlist_cmp_func_t compare)
{
    sortedlist_t *new_list = NULL;

    assert(compare);

    new_list = (sortedlist_t *)malloc(sizeof(struct sortedlist));
    if (NULL == new_list)
    {
        return NULL;
    }
    new_list->list = DllistCreate();
    if (NULL == new_list->list)
    {
        free(new_list);
        return NULL;
    }
    new_list->compare = compare;

    return new_list;
}

void SortedlistDestroy(sortedlist_t *list)
{
    assert(list);
    assert(list->list);

    DllistDestroy(list->list);
    free(list);
}

sortedlist_iter_t SortedlistNext(sortedlist_iter_t iter)
{
    assert(iter.iter);

    iter.iter = DllistNext(iter.iter);

    return iter;
}

sortedlist_iter_t SortedlistPrev(sortedlist_iter_t iter)
{
    sortedlist_iter_t before_iter = {NULL, NULL};
    assert(iter.iter);

    before_iter.iter = DllistPrev(iter.iter);

    return before_iter;
}

sortedlist_iter_t SortedlistGetBegin(const sortedlist_t *list)
{
    sortedlist_iter_t begin = {NULL, NULL};
    assert(list);
    assert(list->list);

    begin.iter = DllistGetBegin(list->list);

    return begin;
}

sortedlist_iter_t SortedlistGetEnd(const sortedlist_t *list)
{
    sortedlist_iter_t end = {NULL, NULL};
    assert(list);
    assert(list->list);

    end.iter = DllistGetEnd(list->list);

    return end;
}

sortedlist_iter_t SortedlistInsert(sortedlist_t *list, void *data)
{
    sortedlist_iter_t runner = {NULL, NULL};
    assert(list);
    assert(data);

    runner = SortedlistGetBegin(list);
    while ((0 == SortedlistIsSameIter(runner, SortedlistGetEnd(list))) && 
           (0 >= list->compare(SortedlistGetData(runner), data)))
    {
        runner = SortedlistNext(runner);
    }
    runner.iter = DllistInsertBefore(list->list, data, runner.iter);

    return runner;
}

sortedlist_iter_t SortedlistRemove(sortedlist_iter_t where)
{
    sortedlist_iter_t next = {NULL, NULL};
    assert(where.iter);

    next.iter = DllistRemove(where.iter);

    return next;
}

size_t SortedlistSize(const sortedlist_t *list)
{
    assert(list);
    assert(list->list);

    return DllistSize(list->list);
}

void *SortedlistGetData(sortedlist_iter_t iter)
{
    assert(iter.iter);

    return DllistGetData(iter.iter);
}

sortedlist_iter_t SortedlistFind(sortedlist_t *list, sortedlist_iter_t from,
                                        sortedlist_iter_t to, const void *param)
{
    assert(list);
    assert(from.iter);
    assert(to.iter);
    assert(param);

    while ((0 == SortedlistIsSameIter(from, to)) && 
           (0 != list->compare(SortedlistGetData(from), param)
           && list->compare(SortedlistGetData(from), param) < 0))
    {
        from = SortedlistNext(from);
    }

    return from;
}

sortedlist_iter_t SortedlistFindIf(sortedlist_iter_t from, sortedlist_iter_t to,
              int (*is_match)(const void *data, const void *param), void *param)

{
    assert(from.iter);
    assert(to.iter);
    assert(is_match);
    assert(from.list == to.list);

	from.iter = DllistFind(param, from.iter, to.iter , is_match);

    return from;
}

int SortedlistIsSameIter(sortedlist_iter_t iter1, sortedlist_iter_t iter2)
{
    assert(iter1.iter);
    assert(iter2.iter);

    return DllistIsSameIter(iter1.iter, iter2.iter);
}

int SortedlistIsEmpty(const sortedlist_t *list)
{
    assert(list);
    assert(list->list);

    return DllistIsEmpty(list->list);
}

void *SortedlistPopFront(sortedlist_t *list)
{
    assert(list);
    assert(list->list);

    return DllistPopFront(list->list);
}

void *SortedlistPopBack(sortedlist_t *list)
{
    assert(list);
    assert(list->list);

    return DllistPopBack(list->list);
}

void SortedlistMerge(sortedlist_t *dest, sortedlist_t *src)
{
    sortedlist_iter_t runner_src = {NULL, NULL};
    sortedlist_iter_t runner_dest = {NULL, NULL};
    assert(src);
    assert(dest);
    assert(dest->compare == src->compare);

    runner_src = SortedlistGetBegin(src);
    runner_dest = SortedlistGetBegin(dest);

    while ((0 == SortedlistIsSameIter(runner_src, SortedlistGetEnd(src))))
    {
        if ((0 == SortedlistIsSameIter(runner_dest, SortedlistGetEnd(dest)))
        				  && (0 >= dest->compare(SortedlistGetData(runner_dest),
        										SortedlistGetData(runner_src))))
        {
            runner_dest = SortedlistNext(runner_dest);
        }
        else
        {
            DllistSplice(runner_dest.iter, runner_src.iter,
            								   SortedlistNext(runner_src).iter);
            runner_src = SortedlistGetBegin(src);
        }
    }
}

int SortedlistForEach(sortedlist_iter_t from, sortedlist_iter_t to,
                      int (*action)( void *data,  void *param), void *param)
{
    assert(from.iter);
    assert(to.iter);
    assert(action);

    return DllistForEach(from.iter, to.iter, action, param);
}

