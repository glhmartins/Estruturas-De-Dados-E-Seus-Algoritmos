int nf(TAB *a){
  if (!a) return 0;
  if ((a) && (!a->esq) && (!a->dir)) return 1;
  return nf(a->dir) + nf(a->esq);
}