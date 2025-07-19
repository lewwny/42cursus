# Libft

> 📚 Ma propre bibliothèque standard C — My custom C standard library

## 🇫🇷 À propos

`libft` est le tout premier projet du cursus 42.  
Le but est de recréer une version personnelle de plusieurs fonctions de la librairie standard C (`<string.h>`, `<ctype.h>`, etc.), en respectant strictement les normes de codage de 42.

Ce projet permet de renforcer la compréhension de la gestion mémoire, des pointeurs, des chaînes de caractères, et de la rigueur du C bas niveau.

## 🇬🇧 About

`libft` is the very first project of the 42 curriculum.  
The goal is to reimplement a selection of standard C library functions (`<string.h>`, `<ctype.h>`, etc.) in a personal library, following the strict 42 coding standards.

This project helps build a solid foundation in memory management, pointers, string handling, and low-level C discipline.

---

## 🧠 Contenu / Content

La librairie comprend notamment :

- Fonctions de la libc (`ft_memcpy`, `ft_strncmp`, `ft_atoi`, etc.)
- Fonctions supplémentaires utiles (`ft_split`, `ft_itoa`, `ft_strtrim`, etc.)
- Fonctions de gestion de listes chaînées (`ft_lstnew`, `ft_lstadd_back`, `ft_lstclear`, etc.)

---

## 🛠️ Compilation

Pour compiler la librairie :

```bash
make        # Compile libft.a
make clean  # Supprime les fichiers objets
make fclean # Supprime les fichiers objets et la librairie
make re     # Recompile tout depuis zéro