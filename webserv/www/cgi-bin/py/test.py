#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import warnings
# from urllib3.exceptions import NotOpenSSLWarning

warnings.filterwarnings(
    "ignore",
    message=r".*urllib3 v2 only supports OpenSSL 1\.1\.1\+.*",
    category=Warning,
    module=r"urllib3(\.|$)"
)

import os
import sys
import html
import random
import cgi
from datetime import date
from google.genai import types



try:
	# Essayez d'importer la lib "google-genai" moderne
	# pip install google-genai
	from google import genai  # google-genai >= 1.0
	LIB_MODE = "client"
except Exception:
	# Fallback pour l'ancien SDK "google-generativeai"
	# pip install google-generativeai
	import google.generativeai as genai  # type: ignore
	LIB_MODE = "generativemodel"


def here(*parts) -> str:
	"""Chemin absolu basé sur ce fichier, fiable en CGI."""
	return os.path.join(os.path.dirname(os.path.abspath(__file__)), *parts)


def openfile() -> str:
	with open(here("../../decouvrir.html"), "r", encoding="utf-8") as f:
		return f.read()


def openprompt() -> str:
	with open(here("prompt.txt"), "r", encoding="utf-8") as f:
		return f.read()


def cgi_write_headers_ok():
	sys.stdout.write(
		"Status: 200 OK\r\n"
		"Content-Type: text/html; charset=utf-8\r\n"
		"Cache-Control: no-store\r\n"
		"\r\n"
	)


def cgi_error_response(error_msg: str):
	sys.stdout.write(
		"Status: 500 Internal Server Error\r\n"
		"Content-Type: text/html; charset=utf-8\r\n"
		"Cache-Control: no-store\r\n"
		"\r\n"
		"<html><head><title>500 Internal Server Error</title></head>"
		"<body><h1>500 Internal Server Error</h1>"
		"<p>Une erreur est survenue lors de l'exécution du script CGI."
		"<br>" + html.escape(error_msg) + "</p>"
		"</body></html>"
	)


def get_model_text(prompt: str) -> str:
	api_key = "AIzaSyAR47kNaGDqOc4Cd3XgPPXhXPJr7cULDDM"  # Clé d'API publique pour test uniquement

	element = os.environ.get("HTTP_COOKIE")
	if element:
		parts = element.split(";")
		for part in parts:
			part = part.strip()
			if part.startswith("element="):
				element = part[len("element="):]
				break
	else:
		element = "l'amour"
	if LIB_MODE == "client":
		client = genai.Client(api_key=api_key)
		resp = client.models.generate_content(
			model="gemini-2.5-flash",
			contents=prompt + str(date.today()) + " pimente l'horoscope avec cet element :" + element,
			config=types.GenerateContentConfig(  # <-- remplace generation_config=...
				temperature=0.9,
			),
		)
		text = getattr(resp, "text", None) or getattr(resp, "output_text", None)
		if not text and hasattr(resp, "candidates") and resp.candidates:
			text = str(resp.candidates[0])
		if not text:
			raise RuntimeError("Réponse du modèle vide ou non reconnue.")
		return text

	else:
		# Ancien SDK "google-generativeai"
		genai.configure(api_key=api_key)
		model = genai.GenerativeModel("gemini-2.5-flash")
		resp = model.generate_content(
			prompt,
			generation_config={"temperature": 0.9},  # <-- ici c'est bien generation_config
		)
		text = getattr(resp, "text", None) or getattr(resp, "output_text", None)
		if not text:
			raise RuntimeError("Réponse du modèle vide ou non reconnue (SDK legacy).")
		return text


def main():
	lst_sign = [
		"Sagittaire", "Capricorne", "Verseau", "Poissons", "Bélier", "Taureau",
		"Gémeaux", "Cancer", "Lion", "Vierge", "Balance", "Scorpion"
	]
	form = cgi.FieldStorage()
	signe = form.getfirst("signe", "")
	if signe == "":
		signe = random.choice(lst_sign)

	# cookie = os.environ.get("HTTP_COOKIE")
	template = openfile()
	prompt = openprompt().replace("{{signe}}", signe)

	generated = get_model_text(prompt)

	# Par défaut : échappe le HTML pour éviter toute injection.
	safe_generated = generated.replace("\n", "<br>")

	html_out = template.replace("<!-- texte ici-->", f"<p>{safe_generated}</p>")
	html_out = html_out.replace("style.css", "../../style.css")
	html_out = html_out.replace("index.html", "../../index.html")
	html_out = html_out.replace("signes.html", "../../signes.html")
	html_out = html_out.replace("oracle.html", "../../oracle.html")
	html_out = html_out.replace("contact.html", "../../contact.html")

	cgi_write_headers_ok()
	sys.stdout.write(html_out)


if __name__ == "__main__":
	try:
		main()
	except Exception as e:
		import traceback
		traceback.print_exc()
		cgi_error_response(str(e))