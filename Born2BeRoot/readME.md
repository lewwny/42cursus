# Born2beRoot

> 🔐 Configuration complète d’un serveur Linux sécurisé et monitoré  
> 🔐 Full setup of a secure and monitored Linux server

---

## 🇫🇷 À propos

**Born2beRoot** est un projet du tronc commun de 42 visant à apprendre à configurer, sécuriser et surveiller un serveur Linux (Debian ou Alpine).  
L'objectif est de mettre en place un système minimaliste mais robuste, respectant des critères stricts de sécurité, de gestion des utilisateurs et de monitoring système.

Ce projet m’a permis de maîtriser :

- Le partitionnement manuel et le chiffrement de disque via LUKS
- L’installation et la configuration de SSH, UFW, et sudo
- La gestion des utilisateurs, groupes et politiques de mot de passe
- La configuration avancée de `sudo` avec journalisation
- L’écriture de scripts Bash de monitoring et leur exécution automatique via `cron`

---

## 🇬🇧 About

**Born2beRoot** is a 42 project that teaches how to install, secure, and monitor a Linux server (Debian or Alpine).  
The goal is to build a minimal but secure system with strict access, encryption, password policy, and user monitoring.

Through this project, I gained experience with:

- Manual disk partitioning and full encryption with LUKS
- Setting up SSH, UFW firewall, and secure `sudo` policies
- Creating and managing users, groups, and password rules
- Advanced `sudo` logging and terminal restrictions
- Writing and scheduling custom Bash scripts for system monitoring

---

## 🛠️ Configuration système

### 🧩 Partitionnement chiffré (LUKS)

- `/boot` séparé
- Partition LUKS contenant :
  - `/` (root)
  - `/home`
  - swap

Chiffrement : **XavierNiel42!**

---

### 🔐 Accès utilisateur

- **Nom d'utilisateur** : `XXX`
- **Mot de passe utilisateur** : `XXX`
- **Mot de passe root** : `XXX`

---

### 📡 SSH sécurisé

- Port personnalisé : `4242`
- Interdiction de connexion directe à `root`
- Activation du pare-feu UFW :
  - Autorise uniquement le port 4242
  - Blocage des connexions entrantes par défaut
  - Autorisation des connexions sortantes

---

### 👤 Gestion des utilisateurs et sécurité

- Création manuelle d’utilisateurs/groupes
- Ajout à des groupes via `usermod`
- Mot de passe complexe et expiration forcée :
  - Longueur ≥ 10
  - Au moins 1 majuscule, 1 minuscule, 1 chiffre
  - Limitation des répétitions
  - Expiration et avertissement configurés
- Configuration via :
  - `/etc/login.defs`
  - `/etc/security/pwquality.conf`
  - `/etc/pam.d/common-password`

---

### 🛡️ Politique sudo renforcée

- Configuration dans `visudo` :
  - 3 essais de mot de passe maximum
  - Message d’erreur personnalisé
  - Journalisation des commandes sudo (`/var/log/sudo/sudo.log`)
  - Activation de la journalisation input/output
  - Utilisation obligatoire d’un terminal (`requiretty`)
  - Définition d’un chemin système sécurisé (`secure_path`)

---

## 📊 Script de monitoring automatisé

Script Bash (`monitoring.sh`) exécuté toutes les 10 minutes via `cron` :

- Affiche via `wall` :
  - Architecture, CPU physique/virtuel
  - RAM et espace disque utilisés
  - Charge CPU
  - Dernier démarrage
  - Nombre de connexions TCP établies
  - Nombre d’utilisateurs connectés
  - Adresse IP et MAC
  - Nombre de commandes `sudo` utilisées

Activation du script avec :

```bash
chmod +x monitoring.sh
crontab -e