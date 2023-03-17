#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
 
#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // getline сама выделит память
  getline(&line, &bufsize, stdin);
  return line;
}
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;
  
  if (!tokens) {
    fprintf(stderr, "lsh: ошибка выделения памяти\n");
    exit(EXIT_FAILURE);
  }
  
  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;
    
    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
      }
    }
    
    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}
int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;
  
  pid = fork();
  if (pid == 0) {
    // Дочерний процесс
    char* itog_str[10000]={0};
    for(int i=0; i<sizeof(args);i++){
        strcat(itog_str[i],args[i]);
        printf("%s",itog_str[i]);
        printf("%s",args[i]);
    }
    
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Ошибка при форкинге
    perror("lsh");
  } else {
    // Родительский процесс
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  
  return 1;
}
/*
Объявление функций для встроенных команд оболочки:
*/
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_laba(char **args);

/*
Список встроенных команд, за которыми следуют соответствующие функции
*/
char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "laba"
};

int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_help,
  &lsh_exit,
  &lsh_laba
};
int lsh_laba(char **args)
{
  if(args!=0) {
    execl("/Users/german/Desktop/OC/Laba-1/out","laba.cpp","../Laba-1/first.txt", "../Laba-1/last.txt", "4", "7", "10", NULL);
  }
  return 1;
}
int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
Реализации встроенных функций
*/
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: ожидается аргумент для \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("Наберите название программы и её аргументы и нажмите enter.\n");
  printf("Вот список встроенных команд:\n");
  
  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }
  
  printf("Используйте команду man для получения информации по другим программам.\n");
  return 1;
}

int lsh_exit(char **args)
{
  return 0;
}
int lsh_execute(char **args)
{
  int i;
  
  if (args[0] == NULL) {
    // Была введена пустая команда.
    return 1;
  }
  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  
  return lsh_launch(args);
}
void lsh_loop(void)
{
  char *line;
  char **args;
  int status;
  
  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);
    
    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv)
{
  // Загрузка файлов конфигурации при их наличии.
  
  // Запуск цикла команд.
  lsh_loop();
  
  // Выключение / очистка памяти.
  
  return EXIT_SUCCESS;
}