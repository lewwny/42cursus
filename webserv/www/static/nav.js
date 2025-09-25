// static/nav.js

// Tout le code est encapsulé et s’exécute après le parse du DOM grâce à "defer".
document.addEventListener('DOMContentLoaded', () => {
	// 1) Boutons "Découvrir mon signe"
	const buttons = ['btn-decouvrir', 'btn-decouvrir-home'];
	buttons.forEach((id) => {
	  const btn = document.getElementById(id);
	  if (btn) {
		btn.addEventListener('click', () => {
		  // Utilise un chemin absolu pour éviter /cgi-bin/py/...
		  window.location.href = '/decouvrir.html';
		});
	  }
	});
  
	// 2) Spinner lors de la soumission du formulaire
	const form = document.querySelector('.horoscope-form');
	const loading = document.getElementById('loading');
  
	if (form && loading) {
	  form.addEventListener('submit', () => {
		loading.style.display = 'flex';
	  });
  
	  // Bonus UX : si l'utilisateur revient via le bouton "Précédent",
	  // assure que le spinner est masqué (bfcache)
	  window.addEventListener('pageshow', (evt) => {
		if (evt.persisted) {
		  loading.style.display = 'none';
		}
	  });
	}
  
	// 3) Upload via bouton #upload-btn
	/*const uploadBtn = document.getElementById('upload-btn');
  
	if (uploadBtn) {
	  // Crée l'input file caché s'il n'existe pas déjà
	  let hiddenInput = document.getElementById('hidden-file-input');
	  if (!hiddenInput) {
		hiddenInput = document.createElement('input');
		hiddenInput.type = 'file';
		hiddenInput.id = 'hidden-file-input';
		hiddenInput.style.display = 'none';
		document.body.appendChild(hiddenInput);
	  }
  
	  // Ouvre le sélecteur au clic sur le bouton
	  uploadBtn.addEventListener('click', () => {
		hiddenInput.click();
	  });
  
	  // Quand l'utilisateur choisit un fichier
	  hiddenInput.addEventListener('change', async (event) => {
		const files = event.target.files;
		if (!files || files.length === 0) return;
  
		// Affiche un petit retour immédiat
		const names = Array.from(files).map(f => f.name).join(', ');
		console.log('Fichier(s) sélectionné(s) :', names);
  
		// --- Envoi optionnel au serveur avec fetch + FormData ---
		// Dé-commente ce bloc si ton backend écoute POST /upload
		
		try {
		  const fd = new FormData();
		  // si multiple: Array.from(files).forEach(f => fd.append('monFichier[]', f));
		  fd.append('monFichier', files[0]); // un seul fichier
  
		  const resp = await fetch('/upload', {
			method: 'POST',
			body: fd
		  });
  
		  if (!resp.ok) {
			throw new Error('Échec upload: ' + resp.status + ' ' + resp.statusText);
		  }
  
		  const text = await resp.text();
		  alert('Upload réussi ! ' + text);
		} catch (err) {
		  console.error(err);
		  alert('Une erreur est survenue pendant l’upload.');
		}
		
  
		// Réinitialise l'input pour pouvoir re-sélectionner le même fichier ensuite
		hiddenInput.value = '';
	  });
	}*/
  });