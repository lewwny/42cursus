# pipex

> 🔗 Reproduction du comportement de pipelines Unix en C  
> 🔗 Reproduction of Unix pipelines behavior in C

---

## 🇫🇷 À propos

`pipex` est un projet du tronc commun de l’école 42.  
L'objectif est de comprendre et de recréer le fonctionnement des redirections et des tubes (`|`) dans un shell Unix, en manipulant les processus (`fork`), les descripteurs de fichiers (`dup2`) et les entrées/sorties.

J’ai également implémenté la **gestion complète des multi-pipes** en bonus, permettant d’exécuter des pipelines complexes comme dans un vrai shell.

---

## 🇬🇧 About

`pipex` is a 42 Common Core project.  
Its goal is to understand and reproduce how redirections and pipes (`|`) work in a Unix shell, using low-level system calls such as `fork`, `execve`, `dup2`, and pipes.

I also implemented the **multi-pipe bonus**, enabling full support for shell-like pipelines (`cmd1 | cmd2 | cmd3`...).

---

## 🧪 Comportement attendu / Expected behavior

### Partie obligatoire

Simuler :

```bash
< infile cmd1 | cmd2 > outfile