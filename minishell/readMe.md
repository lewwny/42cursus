# minishell

> 🔥 Votre mini Bash en C — Your very own little Bash in C

---

## 🇫🇷 À propos

**Minishell** est l’un des projets phares du cursus 42.  
Il consiste à développer un **shell interactif minimal** en C, capable de prendre en charge les fonctionnalités essentielles d’un bash : prompt, historique, exécution de commandes, redirections, pipes, variables d’environnement, et gestion des signaux.  

Ce projet a été réalisé **en binôme**, ce qui a renforcé la collaboration et le partage des connaissances en programmation système.

---

## 🇬🇧 About

**Minishell** is one of the flagship projects of the 42 curriculum.  
The goal is to build a **minimal interactive shell** in C, supporting core Bash features: prompt, history, command execution, I/O redirections, pipes, environment variables, and signal handling.  

This work was completed **in a pair**, fostering collaboration and knowledge sharing in system programming.

---

## 🚀 Fonctionnalités implémentées / Implemented Features

| Fonction                    | Description FR                                         | Description EN                                            |
|-----------------------------|--------------------------------------------------------|-----------------------------------------------------------|
| 🔸 Prompt interactif        | Affiche un prompt personnalisé et attend la saisie     | Displays a custom prompt and waits for input              |
| 🔸 Historique               | Navigation et réutilisation des commandes (readline)   | Command history navigation (readline)                     |
| 🔸 Recherche et exécution   | Exécution via `PATH`, chemin relatif ou absolu         | Executes commands via `PATH`, relative/absolute           |
| 🔸 Redirections             | `<`, `>`, `>>`, `<<` (heredoc)                         | `<`, `>`, `>>`, `<<` (heredoc)                            |
| 🔸 Pipes                    | Chaînage de plusieurs commandes avec `|`               | Chaining commands with `|`                                |
| 🔸 Variables d’environnement| Expansion de `$VAR` et `$?`                            | Expands `$VAR` and `$?`                                   |
| 🔸 Gestion des signaux      | `Ctrl-C`(nouveau prompt), `Ctrl-D`(exit), `Ctrl-\`(ignore) | `Ctrl-C`(new prompt), `Ctrl-D`(exit), `Ctrl-\`(noop)  |
| 🔸 Builtins                 | `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`| `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |


---

## 🛠️ Compilation

Dans le dossier `minishell/` :

```bash
make