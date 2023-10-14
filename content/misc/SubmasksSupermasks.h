/** Description: Iterate over all masks and 
 * their submasks in O(3^n).
 */
void submasks(int n) {
  for (int mask = 0; mask < (1 << n); mask++)
    for (int sub = mask; sub; sub = (sub - 1) & mask) {} }
void supermasks(int n) {
  for (int mask = 0; mask < (1 << n); mask++)
    for (int sup = mask; sup < (1 << n); sup = (sup + 1) | mask)
      {} }
