library(tidyverse)
library(tensorflow)
library(keras)
library(stringr)
text <- read.delim("Skoro.txt", header = FALSE)
cat("Длина: ", nchar(text), "\n")
maxlen <- 20
step <- 3

# функция расчћта нового распределения путћм взвешивания вероятностей
reweight_distribution <- function(original_distribution, temperature = 0){
  distribution <- log(original_distribution)/temperature
  distribution <- exp(distribution)
  distribution / sum(distribution)
}

text_indexes <- seq(1, nchar(text) - maxlen, by = step)
# хранение последовательностей
sentences <- str_sub(text, text_indexes, text_indexes + maxlen - 1)
# хранение целей(символы после последовательностей)
next_chars <- str_sub(text, text_indexes + maxlen, text_indexes + maxlen)

cat("Количество последовательностей: ", length(sentences), "\n")