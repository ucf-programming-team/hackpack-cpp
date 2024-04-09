/**
 * Author: Daniel West
 * License: CC0
 * Description: returns min(MAX, a * b) without overflowing 2*MAX. Assumes a,b <= MAX
 * Time: $O(1)$
 * Status: NOT TESTED
 */
#pragma once
const ll MAX = 2e18;
ll mult(ll a, ll b) {
	if (b == 0) return 0;
	if (a >= (MAX + b - 1) / b) return MAX;
	return a * b;
}
