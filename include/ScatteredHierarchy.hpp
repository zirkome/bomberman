#ifndef SCATTEREDHIERARCHY_HPP_
# define SCATTEREDHIERARCHY_HPP_

# include "TypeList.hpp"

template <class TList, template <class> class Handler> class ScatteredHierarchy;

template
<
    class T1,
    class T2,
    template <class> class Handler
>
class ScatteredHierarchy<TypeList<T1, T2>, Handler> : public Handler<T1>,
                                                      public ScatteredHierarchy<T2, Handler>
{
};

template
<
    class T,
    template <class> class Handler
>
class ScatteredHierarchy<TypeList<T, NullType>, Handler> : public Handler<T>
{
};


#endif /* SCATTEREDHIERARCHY_HPP_ */
