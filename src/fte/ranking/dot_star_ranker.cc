#include <iostream>

#include "fte/ranking/dot_star_ranker.h"

#include "ffx/conversions.h"

namespace fte {

namespace ranking {
  
bool DotStarRanker::SetLanguage(const std::string & dfa, uint32_t max_word_length) {
  max_word_len_ = max_word_length;
}

bool DotStarRanker::Unrank(const mpz_class & rank,
                           std::string * word) {
  if (rank == 0) {
    (*word) = "";
  } else {
    DotPlusRanker::Unrank(rank-1, word);
  }
}

bool DotStarRanker::Rank(const std::string & word,
                         mpz_class * rank) {
  if (word == "") {
    (*rank) = 0;
  } else {
    DotPlusRanker::Rank(word, rank);
    ++(*rank);
  }
}

bool DotStarRanker::WordsInLanguage(mpz_class * words_in_language) {
  WordsInLanguage(0, max_word_len_, words_in_language);
}

bool DotStarRanker::WordsInLanguage(uint32_t max_word_length,
                                    mpz_class * words_in_language) {
  WordsInLanguage(0, max_word_length, words_in_language);
}

bool DotStarRanker::WordsInLanguage(uint32_t min_word_length,
                                    uint32_t max_word_length,
                                    mpz_class * words_in_language ) {
  DotPlusRanker::WordsInLanguage(min_word_length, max_word_length, words_in_language);
  ++(*words_in_language);
}


std::string DOT_STAR_DFA = "0	0	0	0\n"
                           "0	0	1	1\n"
                           "0	0	2	2\n"
                           "0	0	3	3\n"
                           "0	0	4	4\n"
                           "0	0	5	5\n"
                           "0	0	6	6\n"
                           "0	0	7	7\n"
                           "0	0	8	8\n"
                           "0	0	9	9\n"
                           "0	0	10	00\n"
                           "0	0	10	01\n"
                           "0	0	12	12\n"
                           "0	0	13	13\n"
                           "0	0	14	14\n"
                           "0	0	15	15\n"
                           "0	0	16	16\n"
                           "0	0	17	17\n"
                           "0	0	18	18\n"
                           "0	0	19	19\n"
                           "0	0	20	20\n"
                           "0	0	21	21\n"
                           "0	0	22	22\n"
                           "0	0	23	23\n"
                           "0	0	24	24\n"
                           "0	0	25	25\n"
                           "0	0	26	26\n"
                           "0	0	27	27\n"
                           "0	0	28	28\n"
                           "0	0	29	29\n"
                           "0	0	30	30\n"
                           "0	0	31	31\n"
                           "0	0	32	32\n"
                           "0	0	33	33\n"
                           "0	0	34	34\n"
                           "0	0	35	35\n"
                           "0	0	36	36\n"
                           "0	0	37	37\n"
                           "0	0	38	38\n"
                           "0	0	39	39\n"
                           "0	0	40	40\n"
                           "0	0	41	41\n"
                           "0	0	42	42\n"
                           "0	0	43	43\n"
                           "0	0	44	44\n"
                           "0	0	45	45\n"
                           "0	0	46	46\n"
                           "0	0	47	47\n"
                           "0	0	48	48\n"
                           "0	0	49	49\n"
                           "0	0	50	50\n"
                           "0	0	51	51\n"
                           "0	0	52	52\n"
                           "0	0	53	53\n"
                           "0	0	54	54\n"
                           "0	0	55	55\n"
                           "0	0	56	56\n"
                           "0	0	57	57\n"
                           "0	0	58	58\n"
                           "0	0	59	59\n"
                           "0	0	60	60\n"
                           "0	0	61	61\n"
                           "0	0	62	62\n"
                           "0	0	63	63\n"
                           "0	0	64	64\n"
                           "0	0	65	65\n"
                           "0	0	66	66\n"
                           "0	0	67	67\n"
                           "0	0	68	68\n"
                           "0	0	69	69\n"
                           "0	0	70	70\n"
                           "0	0	71	71\n"
                           "0	0	72	72\n"
                           "0	0	73	73\n"
                           "0	0	74	74\n"
                           "0	0	75	75\n"
                           "0	0	76	76\n"
                           "0	0	77	77\n"
                           "0	0	78	78\n"
                           "0	0	79	79\n"
                           "0	0	80	80\n"
                           "0	0	81	81\n"
                           "0	0	82	82\n"
                           "0	0	83	83\n"
                           "0	0	84	84\n"
                           "0	0	85	85\n"
                           "0	0	86	86\n"
                           "0	0	87	87\n"
                           "0	0	88	88\n"
                           "0	0	89	89\n"
                           "0	0	90	90\n"
                           "0	0	91	91\n"
                           "0	0	92	92\n"
                           "0	0	93	93\n"
                           "0	0	94	94\n"
                           "0	0	95	95\n"
                           "0	0	96	96\n"
                           "0	0	97	97\n"
                           "0	0	98	98\n"
                           "0	0	99	99\n"
                           "0	0	100	000\n"
                           "0	0	100	001\n"
                           "0	0	102	102\n"
                           "0	0	103	103\n"
                           "0	0	104	104\n"
                           "0	0	105	105\n"
                           "0	0	106	106\n"
                           "0	0	107	107\n"
                           "0	0	108	108\n"
                           "0	0	109	109\n"
                           "0	0	110	010\n"
                           "0	0	110	011\n"
                           "0	0	112	112\n"
                           "0	0	113	113\n"
                           "0	0	114	114\n"
                           "0	0	115	115\n"
                           "0	0	116	116\n"
                           "0	0	117	117\n"
                           "0	0	118	118\n"
                           "0	0	119	119\n"
                           "0	0	120	020\n"
                           "0	0	120	021\n"
                           "0	0	122	122\n"
                           "0	0	123	123\n"
                           "0	0	124	124\n"
                           "0	0	125	125\n"
                           "0	0	126	126\n"
                           "0	0	127	127\n"
                           "0	0	128	128\n"
                           "0	0	129	129\n"
                           "0	0	130	030\n"
                           "0	0	130	031\n"
                           "0	0	132	132\n"
                           "0	0	133	133\n"
                           "0	0	134	134\n"
                           "0	0	135	135\n"
                           "0	0	136	136\n"
                           "0	0	137	137\n"
                           "0	0	138	138\n"
                           "0	0	139	139\n"
                           "0	0	140	040\n"
                           "0	0	140	041\n"
                           "0	0	142	142\n"
                           "0	0	143	143\n"
                           "0	0	144	144\n"
                           "0	0	145	145\n"
                           "0	0	146	146\n"
                           "0	0	147	147\n"
                           "0	0	148	148\n"
                           "0	0	149	149\n"
                           "0	0	150	050\n"
                           "0	0	150	051\n"
                           "0	0	152	152\n"
                           "0	0	153	153\n"
                           "0	0	154	154\n"
                           "0	0	155	155\n"
                           "0	0	156	156\n"
                           "0	0	157	157\n"
                           "0	0	158	158\n"
                           "0	0	159	159\n"
                           "0	0	160	060\n"
                           "0	0	160	061\n"
                           "0	0	162	162\n"
                           "0	0	163	163\n"
                           "0	0	164	164\n"
                           "0	0	165	165\n"
                           "0	0	166	166\n"
                           "0	0	167	167\n"
                           "0	0	168	168\n"
                           "0	0	169	169\n"
                           "0	0	170	070\n"
                           "0	0	170	071\n"
                           "0	0	172	172\n"
                           "0	0	173	173\n"
                           "0	0	174	174\n"
                           "0	0	175	175\n"
                           "0	0	176	176\n"
                           "0	0	177	177\n"
                           "0	0	178	178\n"
                           "0	0	179	179\n"
                           "0	0	180	080\n"
                           "0	0	180	081\n"
                           "0	0	182	182\n"
                           "0	0	183	183\n"
                           "0	0	184	184\n"
                           "0	0	185	185\n"
                           "0	0	186	186\n"
                           "0	0	187	187\n"
                           "0	0	188	188\n"
                           "0	0	189	189\n"
                           "0	0	190	090\n"
                           "0	0	190	091\n"
                           "0	0	192	192\n"
                           "0	0	193	193\n"
                           "0	0	194	194\n"
                           "0	0	195	195\n"
                           "0	0	196	196\n"
                           "0	0	197	197\n"
                           "0	0	198	198\n"
                           "0	0	199	199\n"
                           "0	0	200	200\n"
                           "0	0	201	201\n"
                           "0	0	202	202\n"
                           "0	0	203	203\n"
                           "0	0	204	204\n"
                           "0	0	205	205\n"
                           "0	0	206	206\n"
                           "0	0	207	207\n"
                           "0	0	208	208\n"
                           "0	0	209	209\n"
                           "0	0	210	210\n"
                           "0	0	211	211\n"
                           "0	0	212	212\n"
                           "0	0	213	213\n"
                           "0	0	214	214\n"
                           "0	0	215	215\n"
                           "0	0	216	216\n"
                           "0	0	217	217\n"
                           "0	0	218	218\n"
                           "0	0	219	219\n"
                           "0	0	220	220\n"
                           "0	0	221	221\n"
                           "0	0	222	222\n"
                           "0	0	223	223\n"
                           "0	0	224	224\n"
                           "0	0	225	225\n"
                           "0	0	226	226\n"
                           "0	0	227	227\n"
                           "0	0	228	228\n"
                           "0	0	229	229\n"
                           "0	0	230	230\n"
                           "0	0	231	231\n"
                           "0	0	232	232\n"
                           "0	0	233	233\n"
                           "0	0	234	234\n"
                           "0	0	235	235\n"
                           "0	0	236	236\n"
                           "0	0	237	237\n"
                           "0	0	238	238\n"
                           "0	0	239	239\n"
                           "0	0	240	240\n"
                           "0	0	241	241\n"
                           "0	0	242	242\n"
                           "0	0	243	243\n"
                           "0	0	244	244\n"
                           "0	0	245	245\n"
                           "0	0	246	246\n"
                           "0	0	247	247\n"
                           "0	0	248	248\n"
                           "0	0	249	249\n"
                           "0	0	250	250\n"
                           "0	0	251	251\n"
                           "0	0	252	252\n"
                           "0	0	253	253\n"
                           "0	0	254	254\n"
                           "0	0	255	255\n"
                           "0\n";

}

}
