// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
//#include "terminalconfig.h"

#include "utility.h"
#include "instructions.h"

#ifdef __cplusplus
extern "C" {
#endif
//#include "func.h"

extern uint32_t __get_MSP(void);

#define STDOUT_USART USART1
#define STDERR_USART USART1
#define STDIN_USART USART1

// errno
#undef errno
extern int errno;


/*
 Переменные среды - пустой список.
 */
char *__env[1] = { 0 };
char **environ = __env;

//int _write(int file, char *ptr, int len);

// exit - экстренный выход. В качестве выхода - зацикливаемся.
void _exit(int __attribute__((__unused__)) status)
{
    while (1);
}

// close - закрытие файла - возвращаем ошибку
int _close(int __attribute__((__unused__)) file)
{
    return -1;
}
/*
 execve - передача управления новому процессу - процессов нет -> возвращаем ошибку.
 */
int _execve(char __attribute__((__unused__)) *name, char  __attribute__((__unused__))**argv, char __attribute__((__unused__)) **env)
{
    errno = ENOMEM;
    return -1;
}

/*
 fork = создание нового процесса
 */
int _fork()
{
    errno = EAGAIN;
    return -1;
}

/*
 fstat - состояние открытого файла
 */
int _fstat(int __attribute__((__unused__)) file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 getpid - получить ID текущего процесса
 */

int _getpid()
{
    return 1;
}

/*
 isatty - является ли файл терминалом.
 */
int _isatty(int file)
{
    switch (file)
    {
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
        return 1;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        return 0;
    }
}

/*
 kill - послать сигнал процессу
 */
int _kill(int __attribute__((__unused__)) pid, int __attribute__((__unused__)) sig)
{
    errno = EINVAL;
    return (-1);
}

/*
 link - устанвить новое имя для существующего файла.
 */

int _link(char __attribute__((__unused__)) *old, char __attribute__((__unused__)) *new_)
{
    errno = EMLINK;
    return -1;
}

/*
 lseek - установить позицию в файле
 */
int _lseek(int __attribute__((__unused__)) file, int __attribute__((__unused__)) ptr, int __attribute__((__unused__)) dir)
{
    return 0;
}

/*
 sbrk - увеличить размер области данных, использутся для malloc
 */
caddr_t _sbrk(int incr)
{
    extern char _ebss;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
    {
        heap_end = &_ebss;
    }
    prev_heap_end = heap_end;

    char * stack = (char*) cpu::get_msp();
    if (heap_end + incr > stack)
    {
//        const char * err = "Heap and stack collision\n";

//        _write(STDERR_FILENO, err, 25);
        errno = ENOMEM;
        return (caddr_t) -1;
        //abort ();
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;

}

/*
 read - чтение из файла, у нас пока для чтения есть только stdin
 */

int _read(int __attribute__((__unused__)) file, char __attribute__((__unused__)) *ptr, int __attribute__((__unused__)) len)
{
//    int n;
//    int num = 0;
    //    switch (file)
    //    {
    //    case STDIN_FILENO:
    //        for (n = 0; n < len; n++)
    //        {
    //            while (USART_GetFlagStatus(STDIN_USART, USART_FLAG_RXNE) == RESET);
    //            char c = (char) (USART_ReceiveData(STDIN_USART) & (uint16_t) 0x01FF);
    //            *ptr++ = c;
    //            num++;
    //        }
    //        break;
    //    default:
    //        errno = EBADF;
    //        return -1;
    //    }
    return 0;
}

/*
 stat - состояние открытого файла.
 */

int _stat(const char __attribute__((__unused__)) *filepath, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 times - временная информация о процессе (сколько тиков: системных, процессорных и т.д.)
 */

clock_t _times(struct tms __attribute__((__unused__)) *buf)
{
    return -1;
}

/*
 unlink - удалить имя файла.
 */
int _unlink(char __attribute__((__unused__)) *name)
{
    errno = ENOENT;
    return -1;
}

/*
 wait - ожидания дочерних процессов
 */
int _wait(int __attribute__((__unused__)) *status)
{
    errno = ECHILD;
    return -1;
}

/*
 write - запись в файл - у нас есть только stderr/stdout
 */
int _write([[maybe_unused]] int file, [[maybe_unused]] char *ptr, int len)
{
//    int n;
//    switch (file)
//    {
//    case STDOUT_FILENO: /*stdout*/

//        for (n = 0; n < len; n++) {

//            ConsolePort::putChar(ptr[n]);
//        }
//        break;

//    case STDERR_FILENO: /* stderr */

//        for (n = 0; n < len; n++)  {

//            ConsolePort::putChar(ptr[n]);
//        }
//        break;

//    default:
//        errno = EBADF;
//        return -1;
//    }
    return len;
}

#ifdef __cplusplus
}
#endif


