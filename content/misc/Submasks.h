/** Description: Iterate over all masks and their submasks in
 * O(3^n)
 */

for (int mask = 0; mask < (1 << n); mask++)
  for (int sub = mask; sub; sub = (sub - 1) & mask)
// do thing