/*As estruturas de dados utilizadas virão a partir das descrições
encontradas em data_structures.h e das funções em data_structures.c.*/
// leftrotate function definition

#include "data_structures.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))


//Funções privadas.
static uint32_t reduced_md5(char *initial_msg, size_t initial_len) {
    uint32_t h0, h1, h2, h3;
    // Message (to prepare)
    char *msg = NULL;

    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating

    // r specifies the per-round shift amounts

    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
            0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
            0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
            0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;

    // Pre-processing: adding a single 1 bit
    //append "1" bit to message
    /* Notice: the input bytes are considered as bits strings,
       where the first bit is the most significant bit of the byte.[37] */

    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message

    int new_len;
    for(new_len = initial_len*8 + 1; new_len%512!=448; new_len++);
    new_len /= 8;

    msg = calloc(new_len + 64, 1); // also appends "0" bits
    // (we alloc also 64 extra bytes...)
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit

    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer

    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset<new_len; offset += (512/8)) {

        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *) (msg + offset);

        // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;

        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {

#ifdef ROUNDS
            char *p;
            p=(char *)&a;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], a);

            p=(char *)&b;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], b);

            p=(char *)&c;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], c);

            p=(char *)&d;
            puts("");
#endif


            uint32_t f, g;

            if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;



        }

        // Add this chunk's hash to result so far:

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;

    }

    // cleanup
    free(msg);
    return (h0^h1^h2^h3)%HASHTABLE_SIZE;

}

static void list_add_item(List *lista, void *item, char* key, char key_len)
{
    struct _list_node *current = lista->items;
    lista->size++;
    if (!current)
    {
        lista->items = (struct _list_node *) calloc(1, sizeof(struct _list_node));
        current = lista->items;
    } else {
        while (current->next)
            current = current->next;
        current->next = (struct _list_node *) calloc(1, sizeof(struct _list_node));
        current->next->prev = current;
        current = current->next;
    }
    current->item = item;
    if (key && key_len)
    {
        int min = key_len < MAX_KEY_LEN ? key_len:MAX_KEY_LEN;
        memcpy(current->key, key, min);
    }
}

static List* list_create()
{
    return (List*) calloc(1, sizeof(List));
}

static Small_Hashtable *hashtable_create()
{
    return (Small_Hashtable*) calloc(1, sizeof(Small_Hashtable));
}

static void hashtable_add_item(Small_Hashtable *hashtable, void *item, char *key, size_t key_len)
{
    uint32_t index = reduced_md5(key, key_len)%HASHTABLE_SIZE;
    list_add_item(&(hashtable->items[index]), item, key, key_len);
}

static void* hashtable_get_item(Small_Hashtable *hashtable, char *key, size_t key_len)
{
    struct _list_node *node = (struct _list_node *) hashtable->items[reduced_md5(key, key_len)%HASHTABLE_SIZE].items;

    if (!node)
        return NULL;

    int min = key_len < MAX_KEY_LEN ? key_len:MAX_KEY_LEN;
    while (node && strncmp(key, node->key, min))
        node = node->next;
    return node->item;
}

/*Public functions*/
void professor_novo(Professores *professores, char nome[], char login[], char senha[])
{
    Professor *prof = calloc(1, sizeof(Professor));
    strncpy(prof->nome, nome, NOME_LEN);
    strncpy(prof->login, login, NOME_LEN);
    memcpy(prof->senha, senha, PWD_SIZE); //TODO: Alterar o tamanho da senha e colocar em um define
    hashtable_add_item(professores, (void*)prof, login, strlen(login));
}

Professor * professor_autentica(Professores *professores, char login[], char senha[])
{
    Professor * prof = (Professor*) hashtable_get_item(professores, login, strlen(login));
    if (prof && !memcmp(prof->senha, senha, PWD_SIZE));//TODO: Alterar o tamanho da senha e colocar em um define
    return prof;
    return NULL;
}

Professores *professor_cria_lista() {
    Professores *prof = hashtable_create();
    for (int i = 0; i < HASHTABLE_SIZE; i++)
        prof->items[i].items = NULL;
    return prof;
}

void professor_deleta_lista(Professores *professores)
{
    struct _list_node *prev, *next;
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        prev = professores->items[i].items;
        next = prev->next;
        while (next)
        {
            free(prev);
            prev = next;
            next = next->next;
        }
        free(prev);
    }
    free(professores);
}

void disciplina_novo(Disciplinas *disciplinas, char codigo[], char nome[], char ementa[], Professor *professor)
{
    Disciplina *disc = calloc (1, sizeof(Disciplina));
    strncpy(disc->codigo, codigo, CODIGO_LEN);
    strncpy(disc->nome, nome, NOME_LEN);
    strncpy(disc->ementa, ementa, MAX_LEN);
    disc->professor = professor;
    hashtable_add_item(disciplinas, (void*)disc, codigo, strlen(codigo));
}


Disciplina * disciplina_obtem_por_codigo(Disciplinas *disciplinas, char codigo[]) {
    return (Disciplina*) hashtable_get_item(disciplinas, codigo, strlen(codigo));
}

Disciplinas *disciplina_cria_lista()
{
    Disciplinas *disc = hashtable_create();
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        disc->items[i].items = NULL;
    }
    return disc;
}

void disciplina_deleta_lista(Disciplinas *disc)
{
    struct _list_node *prev, *next;
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        prev = disc->items[i].items;
        next = prev->next;
        while (next)
        {
            free(prev);
            prev = next;
            next = next->next;
        }
        free(prev);
    }
    free(disc);
}