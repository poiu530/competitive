#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "string_view.h"

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MIN(a, b) ((a)<(b) ? (a) : (b))

#define INPUT_BUF_MAX 256
#define HANDS_MAX 1024
#define HAND_LEN 5

typedef struct {
    char cards[HAND_LEN];
    uint32_t bid;
} Hand;

enum {
    HAND_HIGH_CARD = 1,
    HAND_ONE_PAIR,
    HAND_TWO_PAIR,
    HAND_THREE_OF_A_KIND,
    HAND_FULL_HOUSE,
    HAND_FOUR_OF_A_KIND,
    HAND_FIVE_OF_A_KIND,
};

//#define PART2 1

#if PART2

int get_card_strength(char card)
{
    if (card == 'J') return 0;
    
    if (card >= '2' && card <= '9') {
        return (card - '0') - 1;
    }
    
    if (card == 'T') return 9;
    if (card == 'Q') return 10;
    if (card == 'K') return 11;
    if (card == 'A') return 12;
    
    assert(false && "Unreachable");
    return -1;
}

int get_hand_layout_strength(Hand *hand)
{
    int count_j = 0;
    
    int counts[13] = {0};
    for (size_t i = 0; i < HAND_LEN; ++i) {
        if (hand->cards[i] == 'J') {
            ++count_j;
            break;
        }
        
        counts[get_card_strength(hand->cards[i])]++;
    }
    
    int count_1, count_2, count_3, count_4, count_5;
    count_1 = count_2 = count_3 = count_4 = count_5 = 0;
    
    for (size_t i = 0; i < ARRAY_COUNT(counts); ++i) {
        if (counts[i] == 1) ++count_1;
        if (counts[i] == 2) ++count_2;
        if (counts[i] == 3) ++count_3;
        if (counts[i] == 4) ++count_4;
        if (counts[i] == 5) ++count_5;
    }
    
    if (count_5 == 1) return HAND_FIVE_OF_A_KIND;
    if (count_4 == 1 && count_1 == 1) return HAND_FOUR_OF_A_KIND;
    if (count_3 == 1 && count_2 == 1) return HAND_FULL_HOUSE;
    if (count_3 == 1 && count_1 == 2) return HAND_THREE_OF_A_KIND;
    if (count_2 == 2 && count_1 == 1) return HAND_TWO_PAIR;
    if (count_2 == 1 && count_1 == 3) return HAND_ONE_PAIR;
    if (count_1 == 5) return HAND_HIGH_CARD;
    
    assert(false && "Unreachable");
    return 0;
}


#else

int get_card_strength(char card)
{
    if (card >= '2' && card <= '9') {
        return (card - '0') - 2;
    }
    
    if (card == 'T') return 8;
    if (card == 'J') return 9;
    if (card == 'Q') return 10;
    if (card == 'K') return 11;
    if (card == 'A') return 12;
    
    assert(false && "Unreachable");
    return -1;
}

int get_hand_layout_strength(Hand *hand)
{
    int counts[13] = {0};
    for (size_t i = 0; i < HAND_LEN; ++i) {
        counts[get_card_strength(hand->cards[i])]++;
    }
    
    int count_1, count_2, count_3, count_4, count_5;
    count_1 = count_2 = count_3 = count_4 = count_5 = 0;
    for (size_t i = 0; i < ARRAY_COUNT(counts); ++i) {
        if (counts[i] == 1) ++count_1;
        if (counts[i] == 2) ++count_2;
        if (counts[i] == 3) ++count_3;
        if (counts[i] == 4) ++count_4;
        if (counts[i] == 5) ++count_5;
    }
    
    if (count_5 == 1) return HAND_FIVE_OF_A_KIND;
    if (count_4 == 1 && count_1 == 1) return HAND_FOUR_OF_A_KIND;
    if (count_3 == 1 && count_2 == 1) return HAND_FULL_HOUSE;
    if (count_3 == 1 && count_1 == 2) return HAND_THREE_OF_A_KIND;
    if (count_2 == 2 && count_1 == 1) return HAND_TWO_PAIR;
    if (count_2 == 1 && count_1 == 3) return HAND_ONE_PAIR;
    if (count_1 == 5) return HAND_HIGH_CARD;
    
#if 0
    //
    // Check five of a kind.
    //
    for (size_t i = 0; i < ARRAY_COUNT(counts); ++i) {
        if (counts[i] == HAND_LEN) return HAND_FIVE_OF_A_KIND;
    }
    
    //
    // Check four of a kind.
    //
    count_4 = 0;
    count_1 = 0;
    for (size_t i = 0; i < ARRAY_COUNT(counts); ++i) {
        if (counts[i] == 4) ++count_4;
        else if (counts[i] == 1) ++count_1;
    }
    if (count_4 == 1 && count_1 == 1) return HAND_FOUR_OF_A_KIND;
    
    //
    // Check full house.
    //
    count_3 = 0;
    count_2 = 0;
    for (size_t i = 0; i < ARRAY_COUNT(counts); ++i) {
        if (counts[i] == 3) ++count_3;
        if (counts[i] == 2) ++count_2;
    }
    if (count_3 == 1 && count_2 == 1) return HAND_FULL_HOUSE;
#endif
    
    assert(false && "Unreachable");
    return 0;
}

#endif

// Comparison functions:
// a > b  -> 1
// a < b  -> -1
// a == b -> 0

int compare_hands(Hand *a, Hand *b)
{
    int a_strength = get_hand_layout_strength(a);
    int b_strength = get_hand_layout_strength(b);
    if (a_strength > b_strength) return 1;
    if (a_strength < b_strength) return -1;
    
    for (size_t i = 0; i < HAND_LEN; ++i) {
        int as = get_card_strength(a->cards[i]);
        int bs = get_card_strength(b->cards[i]);
        if (as > bs) return 1;
        if (as < bs) return -1;
    }
    
    return 0;
}

int compare_hands_for_qsort(void *a, void *b)
{
    return compare_hands((Hand *) a, (Hand *) b);
}

int main(void)
{
    Hand hands[HANDS_MAX] = {0};
    size_t hand_count = 0;
    
    char input_buf[INPUT_BUF_MAX];
    while (fgets(input_buf, INPUT_BUF_MAX, stdin)) {
        String_View line = sv_lit(input_buf);
        line = sv_trim_char_end(line, '\n');
        
        String_View hand = sv_trim_to_next_char(&line, ' ');
        String_View bid_str = line;
        
        uint32_t bid;
        assert(sv_to_uint32_simple(bid_str, 10, &bid));
        
        // NOTE(pkruszec): If saving, remember to copy the string view data into an owned buffer.
        
        
        assert(hand_count < HANDS_MAX);
        strncpy(hands[hand_count].cards, hand.vals, MIN(hand.count, ARRAY_COUNT(hands[hand_count].cards)));
        hands[hand_count].bid = bid;
        hand_count++;
    }
    
    qsort(hands, hand_count, sizeof(hands[0]), compare_hands_for_qsort);
    
    size_t sum = 0;
    for (size_t i = 0; i < hand_count; ++i) {
        Hand *hand = &hands[i];
        size_t rank = i+1;
        printf("RANK %zu: %.*s: %u (strength = %d)\n", i+1, ARRAY_COUNT(hand->cards), hand->cards, hand->bid, get_hand_layout_strength(hand));
        sum += rank*hand->bid;
    }
    
    // PART 1:
    // 249848171 -> too low
    // 250058342 -> right
    // 
    // PART 2:
    // 249480090 -> too low
    //
    
    printf("SUM: %zu\n", sum);
    
#if 0
    Hand a = {{'3', '3', '3', '3', '2'}, 0};
    Hand b = {{'2', 'A', 'A', 'A', 'A'}, 0};
    printf("compare: %d\n", compare_hands(&a, &b));
#endif
    
    return 0;
}