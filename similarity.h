#ifndef SIMILARITY_H
#define	SIMILARITY_H

#include "postgres.h"

#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/guc.h"


/* case insensitive ? */
#define		PGS_IGNORE_CASE			1

/* maximum string length */
#define		PGS_MAX_STR_LEN			65535

/*
 * Jaro
 */

/* operation's weight */
#define	PGS_JARO_W1					1.0/3.0
#define	PGS_JARO_W2					1.0/3.0
#define	PGS_JARO_WT					1.0/3.0

/* size of the initial prefix considered */
#define	PGS_JARO_PREFIX_SIZE		4

/* scaling factor */
#define	PGS_JARO_SCALING_FACTOR		0.1

/* minimum score for a string that gets boosted */
#define	PGS_JARO_BOOST_THRESHOLD	0.7

/*
 * Levenshtein
 */
#define		PGS_LEV_MIN_COST		0
#define		PGS_LEV_MAX_COST		1

/*
 * Needleman-Wunch
 */

/*
 * Smith-Waterman
 */
/*
XXX simmetrics uses these values
#define		PGS_SW_MIN_COST			-2.0
#define		PGS_SW_MAX_COST			1.0
#define		PGS_SW_GAP_COST			0.5
*/
#define		PGS_SW_MIN_COST			-1.0
#define		PGS_SW_MAX_COST			2.0
#define		PGS_SW_GAP_COST			-1.0

/*
 * Smith-Waterman-Gotoh
 */
#define		PGS_SWG_WINDOW_SIZE		100

/*
 * Soundex
 */
#define		PGS_SOUNDEX_LEN			4
#define		PGS_SOUNDEX_INV_CODE		-1

/*
 * commonly used functions
 */
#define		min2(a, b)			((a < b) ? a : b)
#define		max2(a, b)			((a > b) ? a : b)
#define		min3(a, b, c)		((a < b && a < c) ? a : ((b < c) ? b : c))
#define		max3(a, b, c)		((a > b && a > c) ? a : ((b > c) ? b : c))
#define		max4(a, b, c, d)	((a > b && a > c && a > d) ? a : ((b > c && b > d) ? b : ((c > d) ? c : d)))

/*
 * normalized results?
 */
extern bool	pgs_block_is_normalized;
extern bool	pgs_cosine_is_normalized;
extern bool	pgs_dice_is_normalized;
extern bool	pgs_euclidean_is_normalized;
extern bool	pgs_hamming_is_normalized;
extern bool	pgs_jaccard_is_normalized;
extern bool	pgs_jaro_is_normalized;
extern bool	pgs_jarowinkler_is_normalized;
extern bool	pgs_levenshtein_is_normalized;
extern bool	pgs_matching_is_normalized;
extern bool	pgs_mongeelkan_is_normalized;
extern bool	pgs_nw_is_normalized;
extern bool	pgs_overlap_is_normalized;
extern bool	pgs_qgram_is_normalized;
extern bool	pgs_sw_is_normalized;
extern bool	pgs_swg_is_normalized;

/*
 * how to separate things?
 */
enum
{
	PGS_UNIT_WORD,		/* tokenize by spaces */
	PGS_UNIT_GRAM,		/* tokenize by n-gram */
	PGS_UNIT_ALNUM,		/* tokenize by nonalnum characters */
	PGS_UNIT_CAMELCASE	/* tokenize by camel-case */
};

/*
 * tokenizers per function
 */
extern int	pgs_block_tokenizer;
extern int	pgs_cosine_tokenizer;
extern int	pgs_dice_tokenizer;
extern int	pgs_euclidean_tokenizer;
extern int	pgs_jaccard_tokenizer;
extern int	pgs_matching_tokenizer;
extern int	pgs_mongeelkan_tokenizer;
extern int	pgs_overlap_tokenizer;
extern int	pgs_qgram_tokenizer;

/*
 * thresholds per function
 */
extern float8	pgs_block_threshold;
extern float8	pgs_cosine_threshold;
extern float8	pgs_dice_threshold;
extern float8	pgs_euclidean_threshold;
extern float8	pgs_hamming_threshold;
extern float8	pgs_jaccard_threshold;
extern float8	pgs_jaro_threshold;
extern float8	pgs_jarowinkler_threshold;
extern float8	pgs_levenshtein_threshold;
extern float8	pgs_matching_threshold;
extern float8	pgs_mongeelkan_threshold;
extern float8	pgs_nw_threshold;
extern float8	pgs_overlap_threshold;
extern float8	pgs_qgram_threshold;
extern float8	pgs_sw_threshold;
extern float8	pgs_swg_threshold;

/*
 * gap penalty
 */
extern float8	pgs_nw_gap_penalty;

/*
 * levenshtein.c
 */
int _lev(char *a, char *b, int icost, int dcost);
int _lev_slow(char *a, char *b, int icost, int dcost);

/*
 * similarity.c
 */
int levcost(char a, char b);
int nwcost(char a, char b);
float swcost(char *a, char *b, int i, int j);
float swggapcost(int i, int j);
float megapcost(char *a, char *b, int i, int j);
void _PG_init(void);

/*
 * external function declarations
 */
extern Datum PGDLLEXPORT block(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT block_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT cosine(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT cosine_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT dice(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT dice_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT euclidean(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT euclidean_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT hamming(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT hamming_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT hamming_text(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT hamming_text_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT jaccard(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT jaccard_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT jaro(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT jaro_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT jarowinkler(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT jarowinkler_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT lev(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT lev_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT levslow(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT levslow_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT matchingcoefficient(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT matchingcoefficient_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT mongeelkan(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT mongeelkan_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT needlemanwunsch(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT needlemanwunsch_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT overlapcoefficient(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT overlapcoefficient_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT qgram(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT qgram_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT smithwaterman(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT smithwaterman_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT smithwatermangotoh(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT smithwatermangotoh_op(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT soundex(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT soundex_op(PG_FUNCTION_ARGS);

extern Datum PGDLLEXPORT gin_extract_value_token(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT gin_extract_query_token(PG_FUNCTION_ARGS);
extern Datum PGDLLEXPORT gin_token_consistent(PG_FUNCTION_ARGS);

#endif
