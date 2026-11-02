import * as shiki from './vendor/shiki.browser.js';

document.addEventListener('DOMContentLoaded', async () => {
  /** @type {NodeListOf<HTMLPreElement>} */
  const codeBlocks = document.querySelectorAll('[class*="language-"]');
  // Highlight code blocks
  if (codeBlocks.length) {
    const highlighter = await shiki.getHighlighter({
      theme: 'monokai',
      themes: ['monokai'],
      langs: [
        'asm',
        'cpp',
        'javascript',
        'json',
        'markdown',
        'ruby',
        'sql',
      ],
      paths: {
        themes: '/scripts/vendor',
        languages: '/scripts/vendor',
        wasm: '/scripts/vendor',
      },
    });

    for (const element of codeBlocks) {
      // Extract the language from the class name.
      const classes = element.className.split(/\s+/);
      const languageClass = classes.find((cls) => cls.startsWith('language-'));
      const lang = languageClass.substring('language-'.length);

      // Add an additional new line to match the textarea scroll.
      element.innerHTML = highlighter.codeToHtml(element.textContent, lang);
    }
  }

  // Ensure we are setup correctly based on preferences.
  if (window.matchMedia && window.matchMedia('(prefers-color-scheme: dark)').matches) {
    if (!localStorage.getItem('dark-mode')) {
      localStorage.setItem('dark-mode', 'true');
    }
  } else if (!localStorage.getItem('dark-mode')) {
    localStorage.setItem('dark-mode', 'false');
  }

  // Dark Mode / Light Mode Theme Toggle
  const themeToggleButton = document.querySelector('.theme-toggle');
  if (themeToggleButton) {
    if (localStorage.getItem('dark-mode') === 'false') {
      themeToggleButton.textContent = '🌝';
      document.body.classList.add('light-theme');
      document.body.classList.remove('dark-theme');
    } else if ((localStorage.getItem('dark-mode') === 'true')) {
      themeToggleButton.textContent = '🌚';
      document.body.classList.remove('light-theme');
      document.body.classList.add('dark-theme');
    }

    themeToggleButton.addEventListener('click', () => {
      const darkMode = themeToggleButton.textContent === '🌚';
      if (darkMode) {
        themeToggleButton.textContent = '🌝';
        document.body.classList.add('light-theme');
        document.body.classList.remove('dark-theme');
        localStorage.setItem('dark-mode', 'false');
      } else {
        themeToggleButton.textContent = '🌚';
        document.body.classList.remove('light-theme');
        document.body.classList.add('dark-theme');
        localStorage.setItem('dark-mode', 'true');
      }
    });
  }

  // Detect Scroll Direction (Unused)
  // let lastScrollTop = 0;
  // let scrollDirectionDown = true;
  // window.addEventListener('scroll', () => {
  //   // Credits: "https://github.com/qeremy/so/blob/master/so.dom.js#L426"
  //   var st = window.pageYOffset || document.documentElement.scrollTop;
  //   if (st > lastScrollTop){
  //     // downscroll code
  //     scrollDirectionDown = true;
  //   } else {
  //      // upscroll code
  //     scrollDirectionDown = false;
  //   }
  //    lastScrollTop = st <= 0 ? 0 : st; // For Mobile or negative scrolling
  // }, false);

  // Table of Contents Highlight
  const observer = new IntersectionObserver((entries) => {
    entries.forEach((entry) => {
      const id = entry.target.getAttribute('id');
      const element = document.querySelector(`.table-of-contents li a[href="#${id}"]`);
      if (element && element.parentElement) {
        if (entry.intersectionRatio > 0) {
          element.parentElement.classList.add('active');
        } else {
          element.parentElement.classList.remove('active');
        }
      }
    });
  });

  // Track all sections that have an `id` applied
  document.querySelectorAll('h2[id], h3[id], h4[id]').forEach((element) => observer.observe(element));
});

// if ('serviceWorker' in navigator) {
//   try {
//     let registration;
//     const registerServiceWorker = async () => {
//       // https://developer.mozilla.org/en-US/docs/Web/API/ServiceWorkerContainer/register
//       registration = await navigator.serviceWorker.register('/service-worker.js', {
//         scope: '/',
//       });
//       if (registration.installing) {
//         // console.log('Service worker installing');
//       } else if (registration.waiting) {
//         // console.log('Service worker installed');
//       } else if (registration.active) {
//         // console.log('Service worker active');
//       }
//     };
//     registerServiceWorker();
//   } catch (error) {
//     // console.error(`Registration failed with ${error}`);
//   }
// }
