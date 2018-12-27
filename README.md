# Dictionary

Simple dictionary program in C.


## Getting Started

Dictionary works immediately, but may have some unexpected behavior if certain "methods" aren't "overidden". Depending on the struct that you plan to use for keys, consider overriding the "key_comparator" but writing a function with the same signature, and passing it to "set_key_comparator". Other implementations that can be overriden include "key_to_string", "value_to_string" for proper printing, and more.

## Authors

* **Jonathan Delgado** - [Otanan](https://github.com/Otanan)