#ifndef AIRSPEED_TABLE_H_
#define AIRSPEED_TABLE_H_

#define MIN_TEMP   -100 /* celsius / 10 */
#define MAX_TEMP   400  /* celsius / 10 */

static const uint16_t zerocomp_table[] = {
  34 , // -10 celsius
  34 , // -9.9 celsius
  33 , // -9.8 celsius
  33 , // -9.7 celsius
  33 , // -9.6 celsius
  32 , // -9.5 celsius
  32 , // -9.4 celsius
  32 , // -9.3 celsius
  32 , // -9.2 celsius
  32 , // -9.1 celsius
  31 , // -9.0 celsius
  31 , // -8.9 celsius
  31 , // -8.8 celsius
  31 , // -8.7 celsius
  31 , // -8.6 celsius
  31 , // -8.5 celsius
  30 , // -8.4 celsius
  30 , // -8.3 celsius
  30 , // -8.2 celsius
  30 , // -8.1 celsius
  30 , // -8.0 celsius
  30 , // -7.9 celsius
  30 , // -7.8 celsius
  30 , // -7.7 celsius
  30 , // -7.6 celsius
  30 , // -7.5 celsius
  30 , // -7.4 celsius
  30 , // -7.3 celsius
  30 , // -7.2 celsius
  30 , // -7.1 celsius
  30 , // -7.0 celsius
  30 , // -6.9 celsius
  30 , // -6.8 celsius
  30 , // -6.7 celsius
  30 , // -6.6 celsius
  30 , // -6.5 celsius
  31 , // -6.4 celsius
  31 , // -6.3 celsius
  31 , // -6.2 celsius
  31 , // -6.1 celsius
  31 , // -6.0 celsius
  31 , // -5.9 celsius
  31 , // -5.8 celsius
  32 , // -5.7 celsius
  32 , // -5.6 celsius
  32 , // -5.5 celsius
  32 , // -5.4 celsius
  33 , // -5.3 celsius
  33 , // -5.2 celsius
  33 , // -5.1 celsius
  33 , // -5.0 celsius
  34 , // -4.9 celsius
  34 , // -4.8 celsius
  34 , // -4.7 celsius
  35 , // -4.6 celsius
  35 , // -4.5 celsius
  35 , // -4.4 celsius
  36 , // -4.3 celsius
  36 , // -4.2 celsius
  36 , // -4.1 celsius
  37 , // -4.0 celsius
  37 , // -3.9 celsius
  38 , // -3.8 celsius
  38 , // -3.7 celsius
  38 , // -3.6 celsius
  39 , // -3.5 celsius
  39 , // -3.4 celsius
  40 , // -3.3 celsius
  40 , // -3.2 celsius
  41 , // -3.1 celsius
  41 , // -3.0 celsius
  42 , // -2.9 celsius
  42 , // -2.8 celsius
  43 , // -2.7 celsius
  43 , // -2.6 celsius
  44 , // -2.5 celsius
  44 , // -2.4 celsius
  45 , // -2.3 celsius
  45 , // -2.2 celsius
  46 , // -2.1 celsius
  47 , // -2.0 celsius
  47 , // -1.9 celsius
  48 , // -1.8 celsius
  48 , // -1.7 celsius
  49 , // -1.6 celsius
  50 , // -1.5 celsius
  50 , // -1.4 celsius
  51 , // -1.3 celsius
  52 , // -1.2 celsius
  52 , // -1.1 celsius
  53 , // -1.0 celsius
  54 , // -0.9 celsius
  54 , // -0.8 celsius
  55 , // -0.7 celsius
  56 , // -0.6 celsius
  56 , // -0.5 celsius
  57 , // -0.4 celsius
  58 , // -0.3 celsius
  59 , // -0.2 celsius
  59 , // -0.1 celsius
  60 , // -1.87905246918e-14 celsius
  61 , // 0.1 celsius
  62 , // 0.2 celsius
  62 , // 0.3 celsius
  63 , // 0.4 celsius
  64 , // 0.5 celsius
  65 , // 0.6 celsius
  66 , // 0.7 celsius
  66 , // 0.8 celsius
  67 , // 0.9 celsius
  68 , // 1.0 celsius
  69 , // 1.1 celsius
  70 , // 1.2 celsius
  71 , // 1.3 celsius
  71 , // 1.4 celsius
  72 , // 1.5 celsius
  73 , // 1.6 celsius
  74 , // 1.7 celsius
  75 , // 1.8 celsius
  76 , // 1.9 celsius
  77 , // 2.0 celsius
  78 , // 2.1 celsius
  79 , // 2.2 celsius
  80 , // 2.3 celsius
  80 , // 2.4 celsius
  81 , // 2.5 celsius
  82 , // 2.6 celsius
  83 , // 2.7 celsius
  84 , // 2.8 celsius
  85 , // 2.9 celsius
  86 , // 3.0 celsius
  87 , // 3.1 celsius
  88 , // 3.2 celsius
  89 , // 3.3 celsius
  90 , // 3.4 celsius
  91 , // 3.5 celsius
  92 , // 3.6 celsius
  93 , // 3.7 celsius
  94 , // 3.8 celsius
  95 , // 3.9 celsius
  96 , // 4.0 celsius
  97 , // 4.1 celsius
  98 , // 4.2 celsius
  99 , // 4.3 celsius
  101 , // 4.4 celsius
  102 , // 4.5 celsius
  103 , // 4.6 celsius
  104 , // 4.7 celsius
  105 , // 4.8 celsius
  106 , // 4.9 celsius
  107 , // 5.0 celsius
  108 , // 5.1 celsius
  109 , // 5.2 celsius
  110 , // 5.3 celsius
  111 , // 5.4 celsius
  113 , // 5.5 celsius
  114 , // 5.6 celsius
  115 , // 5.7 celsius
  116 , // 5.8 celsius
  117 , // 5.9 celsius
  118 , // 6.0 celsius
  119 , // 6.1 celsius
  121 , // 6.2 celsius
  122 , // 6.3 celsius
  123 , // 6.4 celsius
  124 , // 6.5 celsius
  125 , // 6.6 celsius
  126 , // 6.7 celsius
  128 , // 6.8 celsius
  129 , // 6.9 celsius
  130 , // 7.0 celsius
  131 , // 7.1 celsius
  132 , // 7.2 celsius
  134 , // 7.3 celsius
  135 , // 7.4 celsius
  136 , // 7.5 celsius
  137 , // 7.6 celsius
  139 , // 7.7 celsius
  140 , // 7.8 celsius
  141 , // 7.9 celsius
  142 , // 8.0 celsius
  143 , // 8.1 celsius
  145 , // 8.2 celsius
  146 , // 8.3 celsius
  147 , // 8.4 celsius
  148 , // 8.5 celsius
  150 , // 8.6 celsius
  151 , // 8.7 celsius
  152 , // 8.8 celsius
  154 , // 8.9 celsius
  155 , // 9.0 celsius
  156 , // 9.1 celsius
  157 , // 9.2 celsius
  159 , // 9.3 celsius
  160 , // 9.4 celsius
  161 , // 9.5 celsius
  162 , // 9.6 celsius
  164 , // 9.7 celsius
  165 , // 9.8 celsius
  166 , // 9.9 celsius
  168 , // 10.0 celsius
  169 , // 10.1 celsius
  170 , // 10.2 celsius
  172 , // 10.3 celsius
  173 , // 10.4 celsius
  174 , // 10.5 celsius
  176 , // 10.6 celsius
  177 , // 10.7 celsius
  178 , // 10.8 celsius
  180 , // 10.9 celsius
  181 , // 11.0 celsius
  182 , // 11.1 celsius
  184 , // 11.2 celsius
  185 , // 11.3 celsius
  186 , // 11.4 celsius
  188 , // 11.5 celsius
  189 , // 11.6 celsius
  190 , // 11.7 celsius
  192 , // 11.8 celsius
  193 , // 11.9 celsius
  194 , // 12.0 celsius
  196 , // 12.1 celsius
  197 , // 12.2 celsius
  198 , // 12.3 celsius
  200 , // 12.4 celsius
  201 , // 12.5 celsius
  202 , // 12.6 celsius
  204 , // 12.7 celsius
  205 , // 12.8 celsius
  206 , // 12.9 celsius
  208 , // 13.0 celsius
  209 , // 13.1 celsius
  211 , // 13.2 celsius
  212 , // 13.3 celsius
  213 , // 13.4 celsius
  215 , // 13.5 celsius
  216 , // 13.6 celsius
  217 , // 13.7 celsius
  219 , // 13.8 celsius
  220 , // 13.9 celsius
  221 , // 14.0 celsius
  223 , // 14.1 celsius
  224 , // 14.2 celsius
  226 , // 14.3 celsius
  227 , // 14.4 celsius
  228 , // 14.5 celsius
  230 , // 14.6 celsius
  231 , // 14.7 celsius
  232 , // 14.8 celsius
  234 , // 14.9 celsius
  235 , // 15.0 celsius
  237 , // 15.1 celsius
  238 , // 15.2 celsius
  239 , // 15.3 celsius
  241 , // 15.4 celsius
  242 , // 15.5 celsius
  243 , // 15.6 celsius
  245 , // 15.7 celsius
  246 , // 15.8 celsius
  248 , // 15.9 celsius
  249 , // 16.0 celsius
  250 , // 16.1 celsius
  252 , // 16.2 celsius
  253 , // 16.3 celsius
  254 , // 16.4 celsius
  256 , // 16.5 celsius
  257 , // 16.6 celsius
  259 , // 16.7 celsius
  260 , // 16.8 celsius
  261 , // 16.9 celsius
  263 , // 17.0 celsius
  264 , // 17.1 celsius
  265 , // 17.2 celsius
  267 , // 17.3 celsius
  268 , // 17.4 celsius
  269 , // 17.5 celsius
  271 , // 17.6 celsius
  272 , // 17.7 celsius
  274 , // 17.8 celsius
  275 , // 17.9 celsius
  276 , // 18.0 celsius
  278 , // 18.1 celsius
  279 , // 18.2 celsius
  280 , // 18.3 celsius
  282 , // 18.4 celsius
  283 , // 18.5 celsius
  284 , // 18.6 celsius
  286 , // 18.7 celsius
  287 , // 18.8 celsius
  288 , // 18.9 celsius
  290 , // 19.0 celsius
  291 , // 19.1 celsius
  292 , // 19.2 celsius
  294 , // 19.3 celsius
  295 , // 19.4 celsius
  296 , // 19.5 celsius
  298 , // 19.6 celsius
  299 , // 19.7 celsius
  300 , // 19.8 celsius
  302 , // 19.9 celsius
  303 , // 20.0 celsius
  304 , // 20.1 celsius
  306 , // 20.2 celsius
  307 , // 20.3 celsius
  308 , // 20.4 celsius
  309 , // 20.5 celsius
  311 , // 20.6 celsius
  312 , // 20.7 celsius
  313 , // 20.8 celsius
  315 , // 20.9 celsius
  316 , // 21.0 celsius
  317 , // 21.1 celsius
  318 , // 21.2 celsius
  320 , // 21.3 celsius
  321 , // 21.4 celsius
  322 , // 21.5 celsius
  323 , // 21.6 celsius
  325 , // 21.7 celsius
  326 , // 21.8 celsius
  327 , // 21.9 celsius
  329 , // 22.0 celsius
  330 , // 22.1 celsius
  331 , // 22.2 celsius
  332 , // 22.3 celsius
  333 , // 22.4 celsius
  335 , // 22.5 celsius
  336 , // 22.6 celsius
  337 , // 22.7 celsius
  338 , // 22.8 celsius
  340 , // 22.9 celsius
  341 , // 23.0 celsius
  342 , // 23.1 celsius
  343 , // 23.2 celsius
  344 , // 23.3 celsius
  346 , // 23.4 celsius
  347 , // 23.5 celsius
  348 , // 23.6 celsius
  349 , // 23.7 celsius
  350 , // 23.8 celsius
  351 , // 23.9 celsius
  353 , // 24.0 celsius
  354 , // 24.1 celsius
  355 , // 24.2 celsius
  356 , // 24.3 celsius
  357 , // 24.4 celsius
  358 , // 24.5 celsius
  359 , // 24.6 celsius
  361 , // 24.7 celsius
  362 , // 24.8 celsius
  363 , // 24.9 celsius
  364 , // 25.0 celsius
  365 , // 25.1 celsius
  366 , // 25.2 celsius
  367 , // 25.3 celsius
  368 , // 25.4 celsius
  369 , // 25.5 celsius
  371 , // 25.6 celsius
  372 , // 25.7 celsius
  373 , // 25.8 celsius
  374 , // 25.9 celsius
  375 , // 26.0 celsius
  376 , // 26.1 celsius
  377 , // 26.2 celsius
  378 , // 26.3 celsius
  379 , // 26.4 celsius
  380 , // 26.5 celsius
  381 , // 26.6 celsius
  382 , // 26.7 celsius
  383 , // 26.8 celsius
  384 , // 26.9 celsius
  385 , // 27.0 celsius
  386 , // 27.1 celsius
  387 , // 27.2 celsius
  388 , // 27.3 celsius
  389 , // 27.4 celsius
  390 , // 27.5 celsius
  391 , // 27.6 celsius
  392 , // 27.7 celsius
  393 , // 27.8 celsius
  394 , // 27.9 celsius
  395 , // 28.0 celsius
  396 , // 28.1 celsius
  396 , // 28.2 celsius
  397 , // 28.3 celsius
  398 , // 28.4 celsius
  399 , // 28.5 celsius
  400 , // 28.6 celsius
  401 , // 28.7 celsius
  402 , // 28.8 celsius
  403 , // 28.9 celsius
  404 , // 29.0 celsius
  404 , // 29.1 celsius
  405 , // 29.2 celsius
  406 , // 29.3 celsius
  407 , // 29.4 celsius
  408 , // 29.5 celsius
  408 , // 29.6 celsius
  409 , // 29.7 celsius
  410 , // 29.8 celsius
  411 , // 29.9 celsius
  412 , // 30.0 celsius
  412 , // 30.1 celsius
  413 , // 30.2 celsius
  414 , // 30.3 celsius
  415 , // 30.4 celsius
  415 , // 30.5 celsius
  416 , // 30.6 celsius
  417 , // 30.7 celsius
  418 , // 30.8 celsius
  418 , // 30.9 celsius
  419 , // 31.0 celsius
  420 , // 31.1 celsius
  420 , // 31.2 celsius
  421 , // 31.3 celsius
  422 , // 31.4 celsius
  422 , // 31.5 celsius
  423 , // 31.6 celsius
  424 , // 31.7 celsius
  424 , // 31.8 celsius
  425 , // 31.9 celsius
  425 , // 32.0 celsius
  426 , // 32.1 celsius
  427 , // 32.2 celsius
  427 , // 32.3 celsius
  428 , // 32.4 celsius
  428 , // 32.5 celsius
  429 , // 32.6 celsius
  429 , // 32.7 celsius
  430 , // 32.8 celsius
  431 , // 32.9 celsius
  431 , // 33.0 celsius
  432 , // 33.1 celsius
  432 , // 33.2 celsius
  433 , // 33.3 celsius
  433 , // 33.4 celsius
  433 , // 33.5 celsius
  434 , // 33.6 celsius
  434 , // 33.7 celsius
  435 , // 33.8 celsius
  435 , // 33.9 celsius
  436 , // 34.0 celsius
  436 , // 34.1 celsius
  436 , // 34.2 celsius
  437 , // 34.3 celsius
  437 , // 34.4 celsius
  438 , // 34.5 celsius
  438 , // 34.6 celsius
  438 , // 34.7 celsius
  439 , // 34.8 celsius
  439 , // 34.9 celsius
  439 , // 35.0 celsius
  440 , // 35.1 celsius
  440 , // 35.2 celsius
  440 , // 35.3 celsius
  440 , // 35.4 celsius
  441 , // 35.5 celsius
  441 , // 35.6 celsius
  441 , // 35.7 celsius
  441 , // 35.8 celsius
  442 , // 35.9 celsius
  442 , // 36.0 celsius
  442 , // 36.1 celsius
  442 , // 36.2 celsius
  442 , // 36.3 celsius
  442 , // 36.4 celsius
  443 , // 36.5 celsius
  443 , // 36.6 celsius
  443 , // 36.7 celsius
  443 , // 36.8 celsius
  443 , // 36.9 celsius
  443 , // 37.0 celsius
  443 , // 37.1 celsius
  443 , // 37.2 celsius
  443 , // 37.3 celsius
  443 , // 37.4 celsius
  443 , // 37.5 celsius
  443 , // 37.6 celsius
  443 , // 37.7 celsius
  443 , // 37.8 celsius
  443 , // 37.9 celsius
  443 , // 38.0 celsius
  443 , // 38.1 celsius
  443 , // 38.2 celsius
  443 , // 38.3 celsius
  443 , // 38.4 celsius
  443 , // 38.5 celsius
  443 , // 38.6 celsius
  443 , // 38.7 celsius
  443 , // 38.8 celsius
  442 , // 38.9 celsius
  442 , // 39.0 celsius
  442 , // 39.1 celsius
  442 , // 39.2 celsius
  442 , // 39.3 celsius
  441 , // 39.4 celsius
  441 , // 39.5 celsius
  441 , // 39.6 celsius
  441 , // 39.7 celsius
  440 , // 39.8 celsius
  440 , // 39.9 celsius
};






#endif /* AIRSPEED_TABLE_H_ */
