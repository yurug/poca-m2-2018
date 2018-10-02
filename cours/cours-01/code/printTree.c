#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct document {
  void (*printItem)        (int);
  void (*startEnumeration) (void);
  void (*stopEnumeration)  (void);
} document_t;

typedef struct tree {
  int           value;
  int           nb_children;
  struct tree** child;
} tree_t;

int value_of  (tree_t* t) {
  return (t->value);
}

int is_leaf (tree_t* t) {
  return (t->nb_children == 0);
}

tree_t* leaf (int x) {
  tree_t* t = (tree_t*) malloc (sizeof (tree_t));
  t->value = x;
  t->nb_children = 0;
  t->child = NULL;
  return (t);
}

tree_t* node (int x, int size, ...) {
  va_list arguments;
  tree_t* t = (tree_t*) malloc (sizeof (tree_t));

  t->value = x;
  t->nb_children = size;
  t->child = (tree_t**) malloc (sizeof (tree_t*) * size);
  va_start (arguments, size);
  for (unsigned int i = 0; i < size; i++) {
    t->child[i] = va_arg (arguments, tree_t*);
  }
  va_end (arguments);
  return (t);
}

void printTree (tree_t* tree, document_t* doc) {
  if (is_leaf (tree)) {
    doc->printItem (value_of (tree));
  } else {
    doc->printItem (value_of (tree));
    doc->startEnumeration ();
    for (unsigned int i = 0; i < tree->nb_children; i++) {
      printTree (tree->child[i], doc);
    }
    doc->stopEnumeration ();
  }
}

void HTMLPrintItem (int x) {
  printf ("<li>%d</li>\n", x);
}

void HTMLStartEnumeration () {
  printf ("<ul>\n");
}

void HTMLStopEnumeration () {
  printf ("</ul>\n");
}

static document_t HTMLdoc = {
  HTMLPrintItem,
  HTMLStartEnumeration,
  HTMLStopEnumeration
};

int main (int argc, char** argv) {
  printTree (node (1, 2,
                   leaf (2),
                   node (3, 2,
                         leaf (4),
                         node (5, 2,
                               leaf (6),
                               leaf (7)))),
             &HTMLdoc);
}
