# ft_printf

> 🖨️ Recréation de la fonction `printf` en C  
> Reimplementation of the `printf` function in C

---

## 🇫🇷 À propos

`ft_printf` est un projet du tronc commun de l’école 42.  
Il consiste à recréer une version personnalisée de la fonction `printf`, capable d’afficher différents types de données formatées, tout en respectant les contraintes de la norme de codage 42.

Ce projet renforce la compréhension de la gestion de la mémoire, de la manipulation de chaînes de caractères et de l’utilisation des fonctions variadiques (`stdarg.h`).

---

## 🇬🇧 About

`ft_printf` is part of the 42 Common Core curriculum.  
The goal is to recreate a custom version of the `printf` function, capable of formatted output for various data types, while adhering to the 42 coding standard.

This project improves understanding of memory management, string manipulation, and variadic functions (`stdarg.h`).

---

## ✅ Conversions gérées / Supported Format Specifiers

| Specifier | Description                      |
|-----------|----------------------------------|
| `%c`      | Affiche un caractère / Character |
| `%s`      | Affiche une chaîne / String      |
| `%p`      | Adresse mémoire (pointeur)       |
| `%d` / `%i` | Entier signé / Signed integer |
| `%u`      | Entier non signé / Unsigned int  |
| `%x`      | Hexadécimal minuscule            |
| `%X`      | Hexadécimal majuscule            |
| `%%`      | Affiche un `%` littéral          |

---

## ⚙️ Compilation

```bash
make        # Compile la bibliothèque libftprintf.a
make clean  # Supprime les fichiers objets
make fclean # Supprime les fichiers objets + la bibliothèque
make re     # Recompile entièrement