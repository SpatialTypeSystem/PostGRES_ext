#ifndef POSTGRES_EXT_PREDICATEENUM_H
#define POSTGRES_EXT_PREDICATEENUM_H

enum class Predicate { disjoint, meet, overlap, covers, contains, equal, inside, coveredBy };

#endif //POSTGRES_EXT_PREDICATEENUM_H
