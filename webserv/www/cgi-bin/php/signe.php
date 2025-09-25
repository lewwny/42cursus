#!/usr/bin/env php
<?php
header("Content-Type: text/html; charset=utf-8");

if (!isset($_POST['naissance'])) {
	echo "<p>Erreur : date de naissance manquante.</p>";
	exit;
}

$naissance = $_POST['naissance'];

// Parser JJ-MM-AAAA
if (!preg_match('/^(\d{2})-(\d{2})-(\d{4})$/', $naissance, $m)) {
	$html = file_get_contents("../../signes.html");

	$extra = "<div style='text-align:center; margin-top:2rem; font-size:1.4rem;'>
				Mauvais format, utilise JJ-MM-AAAA (ex: 25-12-1990)
			</div>";
	$html = str_replace("<!--HERE-->", $extra, $html);
	$html = replace_path($html);
	echo $html;
	exit;
}
$jour = (int)$m[1];
$mois = (int)$m[2];
$annee = (int)$m[3];

function check_year($year) {
	$currentYear = (int)date("Y");
	return ($year > 1900 && $year <= $currentYear);
}

function zodiac($d, $m, $y) {
	if (!check_year($y) || $m < 1 || $m > 12 || $d < 1 || $d > 31)
		return "Inconnu";
	elseif (($m==3 && $d>=21 && $d<=31) || ($m==4 && $d<=19 && $d > 0)) return "Belier";
	elseif (($m==4 && $d>=20 && $d<=30) || ($m==5 && $d<=20 && $d > 0)) return "Taureau";
	elseif (($m==5 && $d>=21 && $d<=31) || ($m==6 && $d<=20 && $d > 0)) return "Gemeaux";
	elseif (($m==6 && $d>=21 && $d<=30) || ($m==7 && $d<=22 && $d > 0)) return "Cancer";
	elseif (($m==7 && $d>=23 && $d<=31) || ($m==8 && $d<=22 && $d > 0)) return "Lion";
	elseif (($m==8 && $d>=23 && $d<=31) || ($m==9 && $d<=22 && $d > 0)) return "Vierge";
	elseif (($m==9 && $d>=23 && $d<=30) || ($m==10 && $d<=22 && $d > 0)) return "Balance";
	elseif (($m==10 && $d>=23 && $d<=31) || ($m==11 && $d<=21 && $d > 0)) return "Scorpion";
	elseif (($m==11 && $d>=22 && $d<=30) || ($m==12 && $d<=21 && $d > 0)) return "Sagittaire";
	elseif (($m==12 && $d>=22 && $d<=31) || ($m==1 && $d<=19 && $d > 0)) return "Capricorne";
	elseif (($m==1 && $d>=20 && $d<=31) || ($m==2 && $d<=18 && $d > 0)) return "Verseau";
	elseif (($m==2 && $d>=19 && $d<=29) || ($m==3 && $d<=20 && $d > 0)) return "Poissons";
	return "Inconnu";
}

function replace_path($html) {
	$tmp = str_replace("index.html", "../../index.html", $html);
	$tmp = str_replace("signes.html", "../../signes.html", $tmp);
	$tmp = str_replace("oracle.html", "../../oracle.html", $tmp);
	$tmp = str_replace("contact.html", "../../contact.html", $tmp);
	$tmp = str_replace("static/nav.js", "../../static/nav.js", $tmp);
	$tmp = str_replace("style.css", "../../style.css", $tmp);
	return $tmp;
}

$signe = zodiac($jour, $mois, $annee);

$html = file_get_contents("../../signes.html");

$extra = "<div style='text-align:center; margin-top:2rem; font-size:1.4rem;'>
			 Ton signe astrologique est : <strong>$signe</strong>
		  </div>";
$html = str_replace("<!--HERE-->", $extra, $html);

$html = replace_path($html);

setcookie("signe", $signe, time() + 3600, "/");
echo $html;
