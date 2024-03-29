//
//  main.c
//  codechef_ PD13_divisor_sumation
//
//  Created by ernesto alvarado on 13/12/19.
//  Copyright © 2019 ernesto alvarado. All rights reserved.
//

// XXX: https://www.codechef.com/PRFT2012/problems/PD13

#if 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#ifndef ONLINE_JUDGE
#include <unistd.h>
#include <sys/time.h>
#endif
#include <math.h>
#include <stdint.h>
#include <ctype.h>

#ifdef COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#if 1
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX LONG_MAX
#endif

#ifndef ULONG_LONG_MAX
#define ULONG_LONG_MAX ULONG_MAX
#endif

#define COMUN_TAM_MAX_LINEA (16*200000)
#define HEAG_LOG_MAX_TAM_CADENA 2000

#define COMUN_BUF_STATICO_TAM 1000
#define COMUN_BUF_STATICO (char[COMUN_BUF_STATICO_TAM] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bit_vector) * 8)

#define COMUN_ASSERT_DUROTE 0
#define COMUN_ASSERT_SUAVECITO 1
#define COMUN_ASSERT_NIMADRES 2

#define COMUN_VALOR_INVALIDO ((tipo_dato)UINT_MAX)
#define COMUN_IDX_INVALIDO ((natural)COMUN_VALOR_INVALIDO)
#define COMUN_FUNC_STATICA static

typedef char byteme;
typedef unsigned int natural;
typedef natural tipo_dato;
typedef long long entero_largo;
typedef unsigned long long entero_largo_sin_signo;
typedef long long bit_vector;

typedef enum BOOLEANOS
{
    falso = 0, verdadero
} bool;

#define COMUN_TIPO_ASSERT COMUN_ASSERT_DUROTE
/*
 #define COMUN_TIPO_ASSERT COMUN_ASSERT_SUAVECITO
 #define COMUN_TIPO_ASSERT COMUN_ASSERT_NIMADRES
 */

#define assert_timeout_dummy(condition) 0;

#if COMUN_TIPO_ASSERT == COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if COMUN_TIPO_ASSERT == COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){while(1){printf("");};abort();}
#endif
#if COMUN_TIPO_ASSERT == COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef COMUN_LOG
#define comun_log_debug(formato, args...) \
do \
{ \
size_t profundidad = 0; \
void *array[HEAG_LOG_MAX_TAM_CADENA]; \
profundidad = backtrace(array, HEAG_LOG_MAX_TAM_CADENA); \
comun_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
} \
while(0);
#else
#define comun_log_debug(formato, args...) 0
#endif

#define comun_max(x,y) ((x) < (y) ? (y) : (x))
#define comun_min(x,y) ((x) < (y) ? (x) : (y))

#define comun_calloc_local(tipo) (&(tipo){0})

void comun_log_debug_func (const char *format, ...);

#ifndef ONLINE_JUDGE
COMUN_FUNC_STATICA void
comun_current_utc_time (struct timespec *ts)
{
    
#ifdef __MACH__
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service (mach_host_self (), CALENDAR_CLOCK, &cclock);
    clock_get_time (cclock, &mts);
    mach_port_deallocate (mach_task_self (), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
#else
#ifdef COMUN_LOG
    clock_gettime (CLOCK_REALTIME, ts);
#endif
#endif
    
}

COMUN_FUNC_STATICA char *
comun_timestamp (char *stime)
{
    time_t ltime;
    long ms;
#ifndef ONLINE_JUDGE
    struct tm result;
    struct timespec spec;
#endif
    char parte_milisecundos[50];
    
    ltime = time (NULL);
    
#ifndef ONLINE_JUDGE
    localtime_r (&ltime, &result);
    asctime_r (&result, stime);
#endif
    
    *(stime + strlen (stime) - 1) = ' ';
    
#ifndef ONLINE_JUDGE
    comun_current_utc_time (&spec);
    ms = round (spec.tv_nsec / 1.0e3);
#endif
    sprintf (parte_milisecundos, "%ld", ms);
    strcat (stime, parte_milisecundos);
    return stime;
}

#endif
#ifdef COMUN_LOG
void
comun_log_debug_func (const char *format, ...)
{
    
    va_list arg;
    va_list arg2;
    const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
    const char *HEADER = "archivo: %s; funcion: %s; linea %d; nivel: %zd 8====D ";
    char formato[HEAG_LOG_MAX_TAM_CADENA + sizeof (HEADER)
                 + sizeof (PEDAZO_TIMESTAMP_HEADER)] = { '\0' };
    char pedazo_timestamp[sizeof (PEDAZO_TIMESTAMP_HEADER) + 100] = { '\0' };
    char cadena_timestamp[100] = { '\0' };
    
    comun_timestamp (cadena_timestamp);
    sprintf (pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);
    
    strcpy (formato, pedazo_timestamp);
    strcat (formato, HEADER);
    strcat (formato, format);
    strcat (formato, "\n");
    
    va_start (arg, format);
    va_copy (arg2, arg);
    vprintf (formato, arg2);
    va_end (arg2);
    va_end (arg);
    setbuf (stdout, NULL);
}
#endif

#ifdef COMUN_LOG
COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena (tipo_dato * arreglo, natural tam_arreglo, char *buffer)
{
    int i;
    char *ap_buffer = NULL;
    int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
    return NULL;
#endif
    
    memset (buffer, 0, 100);
    ap_buffer = buffer;
    
    for (i = 0; i < tam_arreglo; i++)
    {
        characteres_escritos += sprintf (ap_buffer + characteres_escritos,
                                         "%1d", *(arreglo + i));
        if (i < tam_arreglo - 1)
        {
            *(ap_buffer + characteres_escritos++) = ',';
        }
    }
    *(ap_buffer + characteres_escritos) = '\0';
    return ap_buffer;
}

COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena_natural (natural * arreglo,
                                natural tam_arreglo, char *buffer)
{
    int i;
    char *ap_buffer = NULL;
    int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
    return NULL;
#endif
    
    memset (buffer, 0, 100);
    ap_buffer = buffer;
    
    for (i = 0; i < tam_arreglo; i++)
    {
        characteres_escritos +=
        sprintf (ap_buffer + characteres_escritos, "%2u", *(arreglo + i));
        if (i < tam_arreglo - 1)
        {
            *(ap_buffer + characteres_escritos++) = ',';
        }
    }
    *(ap_buffer + characteres_escritos) = '\0';
    return ap_buffer;
}

char *
comun_matrix_a_cadena (tipo_dato * matrix, natural filas_tam,
                       natural columas_tam, char *buffer)
{
    int i;
    natural inicio_buffer_act = 0;
    for (i = 0; i < filas_tam; i++)
    {
        comun_arreglo_a_cadena (matrix + i * columas_tam, columas_tam,
                                buffer + inicio_buffer_act);
        inicio_buffer_act += strlen (buffer + inicio_buffer_act);
        buffer[inicio_buffer_act++] = '\n';
        /*        comun_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer); */
    }
    return buffer;
}

COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena_entero_largo_sin_signo (entero_largo_sin_signo *
                                               arreglo,
                                               entero_largo_sin_signo
                                               tam_arreglo, char *buffer)
{
    int i;
    char *ap_buffer = NULL;
    int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
    return NULL;
#endif
    
    memset (buffer, 0, 100);
    ap_buffer = buffer;
    
    for (i = 0; i < tam_arreglo; i++)
    {
        characteres_escritos += sprintf (ap_buffer + characteres_escritos,
                                         "%llu", *(arreglo + i));
        if (i < tam_arreglo - 1)
        {
            *(ap_buffer + characteres_escritos++) = ',';
        }
    }
    *(ap_buffer + characteres_escritos) = '\0';
    return ap_buffer;
}
#else
COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena (tipo_dato * arreglo, natural tam_arreglo, char *buffer)
{
    return NULL;
}

COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena_natural (natural * arreglo,
                                natural tam_arreglo, char *buffer)
{
    return NULL;
}

char *
comun_matrix_a_cadena (tipo_dato * matrix, natural filas_tam,
                       natural columas_tam, char *buffer)
{
    return NULL;
}

COMUN_FUNC_STATICA char *
comun_arreglo_a_cadena_entero_largo_sin_signo (entero_largo_sin_signo *
                                               arreglo,
                                               entero_largo_sin_signo
                                               tam_arreglo, char *buffer)
{
    return NULL;
}
#endif

#define comun_arreglo_a_cadena_entero_largo_sin_signo_buf_local(a,a_tam) comun_arreglo_a_cadena_entero_largo_sin_signo(a,a_tam,COMUN_BUF_STATICO)
#define comun_arreglo_a_cadena_buf_local(a,a_tam) comun_arreglo_a_cadena(a,a_tam,COMUN_BUF_STATICO)
#define comun_arreglo_a_cadena_natural_buf_local(a,a_tam) comun_arreglo_a_cadena_natural(a,a_tam,COMUN_BUF_STATICO)

COMUN_FUNC_STATICA void
comun_strreplace (char s[], char chr, char repl_chr)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == chr)
        {
            s[i] = repl_chr;
        }
        i++;
    }
}

COMUN_FUNC_STATICA int
comun_lee_matrix_long_stdin (tipo_dato * matrix,
                             int *num_filas, int *num_columnas,
                             int num_max_filas, int num_max_columnas)
{
    int indice_filas = 0;
    int indice_columnas = 0;
    tipo_dato numero = 0;
    char *siguiente_cadena_numero = NULL;
    char *cadena_numero_actual = NULL;
    char *linea = NULL;
    
    linea = calloc (COMUN_TAM_MAX_LINEA, sizeof (char));
    
    while (indice_filas < num_max_filas
           && fgets (linea, COMUN_TAM_MAX_LINEA, stdin))
    {
        indice_columnas = 0;
        cadena_numero_actual = linea;
        comun_strreplace (linea, '\n', '\0');
        if (!strlen (linea))
        {
            comun_log_debug ("weird, linea vacia");
            continue;
        }
        for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
             cadena_numero_actual)
        {
            numero =
            (tipo_dato) strtol (siguiente_cadena_numero, &cadena_numero_actual, 10);
            if (cadena_numero_actual == siguiente_cadena_numero)
            {
                break;
            }
            *(matrix + indice_filas * num_max_columnas + indice_columnas) = numero;
            indice_columnas++;
        }
        if (num_columnas)
        {
            num_columnas[indice_filas] = indice_columnas;
        }
        indice_filas++;
        comun_log_debug ("las filas son %d, con clos %d", indice_filas,
                         indice_columnas);
    }
    
    *num_filas = indice_filas;
    free (linea);
    return 0;
}

COMUN_FUNC_STATICA natural
comun_cuenta_bitchs (tipo_dato num)
{
    natural bit_cnt = 0;
    tipo_dato num_mod = 0;
    num_mod = num;
    while (num_mod)
    {
        num_mod &= ~(num_mod & (-num_mod));
        bit_cnt++;
    }
    return bit_cnt;
}

COMUN_FUNC_STATICA char
comun_letra_a_valor_minuscula (char letra)
{
    return letra - 'a';
}

COMUN_FUNC_STATICA natural
comun_max_natural (natural * nums, natural nums_tam)
{
    natural max = 0;
    int i = 0;
    
    for (i = 0; i < nums_tam; i++)
    {
        natural num_act = nums[i];
        if (num_act > max)
        {
            max = num_act;
        }
    }
    
    return max;
}

COMUN_FUNC_STATICA char *
comun_trimea (char *cad, natural cad_tam)
{
    char tmp = '\0';
    natural i = 0;
    natural j = 0;
    
    comun_log_debug ("entrada %s cad_tam %u", cad, cad_tam);
    while (j < cad_tam && cad[j] != '\0')
    {
        comun_log_debug ("en j %u car %c", j, cad[j]);
        while (j < cad_tam && !isalpha (cad[j]))
        {
            comun_log_debug ("brincando j %u car %c", j, cad[j]);
            j++;
        }
        comun_log_debug ("aora j %u car %c", j, cad[j]);
        if (j == cad_tam)
        {
            comun_log_debug ("q ped");
            break;
        }
        tmp = cad[i];
        cad[i] = cad[j];
        cad[j] = tmp;
        i++;
        j++;
    }
    comun_log_debug ("mierda '%c'", cad[j]);
    
    i = 0;
    while (isalpha (cad[i++]))
        ;
    comun_log_debug ("salida %s", cad);
    cad[i - 1] = '\0';
    
    return cad;
}

#endif

#define COMUN_LIMPIA_MEM(m,s) (memset(m,0,s))
#define COMUN_LIMPIA_MEM_STATICA(m) (memset(m,0,sizeof(*(m))))

COMUN_FUNC_STATICA bool
comun_es_digito (char c)
{
    return c >= '0' && c <= '9';
}

COMUN_FUNC_STATICA byteme
comun_caracter_a_num (char c)
{
    return c - '0';
}

COMUN_FUNC_STATICA void
comun_invierte_arreglo_byteme (byteme * a, natural a_tam)
{
    natural i = 0;
    natural j = a_tam - 1;
    while (i < j)
    {
        byteme t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
}

COMUN_FUNC_STATICA void
comun_invierte_arreglo_natural (natural * a, natural a_tam)
{
    natural i = 0;
    natural j = a_tam - 1;
    while (i < j)
    {
        natural t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
}

COMUN_FUNC_STATICA natural
comun_encuentra_minimo_natural (natural * a, natural a_tam)
{
    natural min = COMUN_VALOR_INVALIDO;
    natural i;
    for (i = 0; i < a_tam; i++)
    {
        if (min > a[i])
        {
            min = a[i];
        }
    }
    return min;
}

COMUN_FUNC_STATICA entero_largo
comun_mcd (entero_largo a, entero_largo b)
{
    entero_largo r = COMUN_VALOR_INVALIDO;
    while (a && b)
    {
        entero_largo tmp = b;
        b = a % b;
        a = tmp;
    }
    
    if (!a)
    {
        r = b;
    }
    if (!b)
    {
        r = a;
    }
    return r;
}

#define comun_compara_tipo(tipo) COMUN_FUNC_STATICA int comun_compara_##tipo(const void *pa, const void *pb) { \
int r = 0; \
tipo a = *(tipo *)pa; \
tipo b = *(tipo *)pb; \
if (a < b) { \
r = -1; \
} else { \
if (a > b) { \
r = 1; \
} \
} \
return r; \
}

comun_compara_tipo (natural) comun_compara_tipo (entero_largo)
COMUN_FUNC_STATICA natural
comun_encuentra_divisores (natural n,
                           natural * divisores, natural divisores_tam)
{
    natural divisores_cnt = 0;
    natural i = 0;
    for (i = 1; i * i < n; i++)
    {
        if (!(n % i))
        {
            assert_timeout (divisores_cnt < divisores_tam);
            divisores[divisores_cnt++] = i;
            assert_timeout (divisores_cnt < divisores_tam);
            divisores[divisores_cnt++] = n / i;
        }
    }
    
    if (i * i == n)
    {
        assert_timeout (divisores_cnt < divisores_tam);
        divisores[divisores_cnt++] = n / i;
    }
    qsort (divisores, divisores_cnt, sizeof (natural), comun_compara_natural);
    return divisores_cnt;
}

#endif


#if 1 /* CRIBA_LINEAL */

typedef struct primos_datos
{
    natural primos_criba_tam;
    natural *primos_criba;
    byteme *primos_criba_es_primo;
    
} primos_datos;

typedef void (*primos_criba_primo_encontrado_cb) (natural primo,
natural idx_primo,
void *cb_ctx);
typedef void (*primos_criba_compuesto_encontrado_cb) (natural primo,
natural idx_primo,
natural
compuesto_origen,
void *cb_ctx);

typedef void (*primos_criba_divisible_encontrado_cb) (natural primo,
natural idx_primo,
natural compuesto,
void *cb_ctx);

typedef void (*primos_criba_no_divisible_encontrado_cb) (natural primo,
natural idx_primo,
natural compuesto,
void *cb_ctx);

#define PRIMOS_CRIBA_USA_CALLBACKS
COMUN_FUNC_STATICA natural
primos_criba_criba (natural limite,
#ifdef PRIMOS_CRIBA_USA_CALLBACKS
                    primos_criba_primo_encontrado_cb primo_cb,
                    primos_criba_compuesto_encontrado_cb compuesto_cb,
                    primos_criba_divisible_encontrado_cb
                    divisible_encontrado_cb,
                    primos_criba_no_divisible_encontrado_cb
                    no_divisible_encontrado_cb,
#endif
                    void *cb_ctx, primos_datos * pd)
{
    natural primos_criba_tam = 0;
    byteme *primos_criba_es_primo = NULL;
    natural *primos_criba = NULL;
    
    pd->primos_criba=calloc(limite+1, sizeof(natural));
    assert_timeout(pd->primos_criba);
    primos_criba=pd->primos_criba;
    
    pd->primos_criba_es_primo=calloc(limite+1, sizeof(byteme));
    assert_timeout(pd->primos_criba_es_primo);
    primos_criba_es_primo=pd->primos_criba_es_primo;
    
    
    comun_log_debug ("primos asta %u", limite);
    natural i, j;
    for (i = 2; i <= limite; i++)
    {
        primos_criba_es_primo[i]=verdadero;
    }
    for (i = 2; i <= limite; i++)
    {
        if (primos_criba_es_primo[i])
        {
            primos_criba[primos_criba_tam++] = i;
#ifdef PRIMOS_CRIBA_USA_CALLBACKS
            if (primo_cb)
            {
                primo_cb (i, primos_criba_tam - 1, cb_ctx);
            }
#endif
        }
        for (j = 0; j < primos_criba_tam && primos_criba[j] * i <= limite; j++)
        {
            
            primos_criba_es_primo[ primos_criba[j] * i]=falso;
#ifdef PRIMOS_CRIBA_USA_CALLBACKS
            if (compuesto_cb)
            {
                compuesto_cb (primos_criba[j], j, i, cb_ctx);
            }
#endif
            if (!(i % primos_criba[j]))
            {
#ifdef PRIMOS_CRIBA_USA_CALLBACKS
                if (divisible_encontrado_cb)
                {
                    divisible_encontrado_cb (primos_criba[j], j, i, cb_ctx);
                }
#endif
                break;
            }
            else
            {
#ifdef PRIMOS_CRIBA_USA_CALLBACKS
                if (no_divisible_encontrado_cb)
                {
                    no_divisible_encontrado_cb (primos_criba[j], j, i, cb_ctx);
                }
#endif
            }
        }
    }
    comun_log_debug ("generados %u primos", primos_criba_tam);
    pd->primos_criba_tam = primos_criba_tam;
    return primos_criba_tam;
}

#endif /* CRIBA_LINEAL */

#if 1 /* pd13 */
#define PD13_MAX_PRIMO ((natural)5E5)
#define PD13_MAX_FACTORES_PRIMOS 10
typedef struct sumas_divisores{
    entero_largo_sin_signo sumas_divisores[PD13_MAX_PRIMO+1];
}sumas_divisores;

void pd13_primo_encontrado(natural primo,
                              natural idx_primo,
                              void *cb_ctx){
    
    sumas_divisores *sd=cb_ctx;
    entero_largo_sin_signo nueva_contribucion_primo=primo+1;

    sd->sumas_divisores[primo]=nueva_contribucion_primo;
}

void pd13_divisible_encontrado (natural primo,
                                   natural idx_primo,
                                   natural compuesto,
                                   void *cb_ctx){
    sumas_divisores *sd=cb_ctx;
    entero_largo_sin_signo *sumas_divisores=sd->sumas_divisores;
    entero_largo_sin_signo nuevo_compuesto=compuesto*primo;
    entero_largo_sin_signo suma_divisores_compuesto=0;
    entero_largo_sin_signo contribucion_primo=1;
    entero_largo_sin_signo nueva_contribucion_primo=0;
    entero_largo_sin_signo complemento_contribucion_primo=0;
    entero_largo_sin_signo suma_divisores_nuevo_compuesto=0;
    entero_largo_sin_signo compuesto_tmp=compuesto;

    while(!(compuesto_tmp%primo)){
        contribucion_primo=contribucion_primo*primo+1;
        compuesto_tmp/=primo;
    }

    suma_divisores_compuesto=sumas_divisores[compuesto];
    
    complemento_contribucion_primo=suma_divisores_compuesto/contribucion_primo;
    
    nueva_contribucion_primo=contribucion_primo*primo+1;
    
    suma_divisores_nuevo_compuesto=complemento_contribucion_primo*nueva_contribucion_primo;
    
    sumas_divisores[nuevo_compuesto]=suma_divisores_nuevo_compuesto;
}

void pd13_no_divisible_encontrado (natural primo,
                                      natural idx_primo,
                                      natural compuesto,
                                      void *cb_ctx){
    sumas_divisores *sd=cb_ctx;
    entero_largo_sin_signo *sumas_divisores=sd->sumas_divisores;
    entero_largo_sin_signo nuevo_compuesto=compuesto*primo;
    entero_largo_sin_signo nueva_contribucion_primo=primo+1;
    entero_largo_sin_signo suma_divisores_nuevo_compuesto=0;

    suma_divisores_nuevo_compuesto=sumas_divisores[compuesto]*nueva_contribucion_primo;
    
    sumas_divisores[nuevo_compuesto]=suma_divisores_nuevo_compuesto;
}

COMUN_FUNC_STATICA void pd13_main(){
    natural t=0;
    entero_largo_sin_signo n=0;
    primos_datos *pd=NULL;
    sumas_divisores *sd=NULL;
    
    sd=calloc(1, sizeof(sumas_divisores));
    assert_timeout(sd);
    
    sd->sumas_divisores[1]=1;
    
    pd=calloc(1, sizeof(primos_datos));
    assert_timeout(pd);
    
    primos_criba_criba(PD13_MAX_PRIMO, pd13_primo_encontrado, NULL, pd13_divisible_encontrado, pd13_no_divisible_encontrado, sd, pd);
    
#ifdef __APPLE__
    if (getenv ("STDIN"))
    {
        if (!freopen (getenv ("STDIN"), "r", stdin))
        {
            printf ("no se pudo stdin con %s", getenv ("STDIN"));
            exit (1);
        }
    }
    if (getenv ("STDOUT"))
    {
        if (!freopen (getenv ("STDOUT"), "w", stdout))
        {
            printf ("no se pudo stdin con %s", getenv ("STDOUT"));
            exit (1);
        }
    }
    if (getenv ("STDERR"))
    {
        if (!freopen (getenv ("STDERR"), "w", stderr))
        {
            printf ("no se pudo stdin con %s", getenv ("STDERR"));
            exit (1);
        }
    }
#endif
    
    scanf("%u",&t);
    while(t--){
        scanf("%llu",&n);
        entero_largo_sin_signo r=sd->sumas_divisores[n];
        printf("%llu\n",r-n);
    }
}

#endif /* pd13 */

int
main (int argc, const char *argv[])
{
    pd13_main();
    return EXIT_SUCCESS;
}

