const SECTIONS = ['home', 'section-1', 'section-2', 'NOTFOUND'];

var lastTabElement, lastSectionElement;

function sectionChanged() {
	section = window.location.hash.substr(2);
	for (let i=0; i < SECTIONS.length; i++) {
		let s = SECTIONS[i];
		if (s == 'NOTFOUND') {
			window.location.href = '#!home';
		} else if (s == section) {
			document.title = 'Brut : ' + TITLES[i];

			if (lastTabElement !== undefined) lastTabElement.classList.remove('current');
			lastTabElement = document.getElementById('tab-'+s);
			lastTabElement.classList.add('current');

			if (lastSectionElement !== undefined) lastSectionElement.classList.remove('current');
			lastSectionElement = document.getElementById('section-'+s);
			lastSectionElement.classList.add('current-inter');
			setTimeout(setCurrentSection, 50, lastSectionElement);

			break;
		}
	}
}

function setCurrentSection(s) {
	s.classList.add('current');
	s.classList.remove('current-inter');
}

function onLoad() {
	if (window.location.hash == '') {
		window.location.href = '#!home';
	} else {
		sectionChanged();
	}
}

window.onload = onLoad;
window.onhashchange = sectionChanged;