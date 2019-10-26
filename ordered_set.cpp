#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less < T>, rb_tree_tag, tree_order_statistics_node_update>;
ordered_set<int> s;
s.insert(1);
s.insert(3);
cout << s.order_of_key(2) << endl;
cout << *s.find_by_order(0) << endl;
