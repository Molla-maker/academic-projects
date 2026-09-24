import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { STLLoader } from 'three/addons/loaders/STLLoader.js';

// DOM Elements
const authButtons = document.getElementById('auth-buttons');
const loginBtn = document.getElementById('login-btn');
const registerBtn = document.getElementById('register-btn');
const logoutBtn = document.getElementById('logout-btn');
const uploadBtn = document.getElementById('upload-btn');
const authForms = document.getElementById('auth-forms');
const loginForm = document.getElementById('login-form');
const registerForm = document.getElementById('register-form');
const loginFormElement = document.getElementById('login-form-element');
const registerFormElement = document.getElementById('register-form-element');
const modelsContainer = document.getElementById('models-container');
const prevPageBtn = document.getElementById('prev-page');
const nextPageBtn = document.getElementById('next-page');
const pageInfo = document.getElementById('page-info');

// State
let currentPage = 1;
let isAuthenticated = false;
let currentSTLModel = null;

// Check authentication status
async function checkAuth() {
  try {
    const response = await fetch('/models/upload');
    isAuthenticated = response.status !== 403;
    updateAuthUI();
  } catch (error) {
    console.error('Error checking auth:', error);
    isAuthenticated = false;
    updateAuthUI();
  }
}

// Update UI based on auth status
function updateAuthUI() {
  if (isAuthenticated) {
    loginBtn.classList.add('hidden');
    registerBtn.classList.add('hidden');
    logoutBtn.classList.remove('hidden');
    uploadBtn.classList.remove('hidden');
  } else {
    loginBtn.classList.remove('hidden');
    registerBtn.classList.remove('hidden');
    logoutBtn.classList.add('hidden');
    uploadBtn.classList.add('hidden');
  }
  authForms.classList.add('hidden');
}

// Show auth form
function showAuthForm(formType) {
  authForms.classList.remove('hidden');
  if (formType === 'login') {
    loginForm.classList.remove('hidden');
    registerForm.classList.add('hidden');
  } else {
    loginForm.classList.add('hidden');
    registerForm.classList.remove('hidden');
  }
}

// Format date
function formatDate(dateString) {
  const date = new Date(dateString);
  return date.toLocaleDateString('en-US', {
    year: 'numeric',
    month: 'long',
    day: 'numeric',
    hour: '2-digit',
    minute: '2-digit'
  });
}

// Three.js setup
const viewer = document.getElementById('viewer');
const width = viewer.clientWidth;
const height = viewer.clientHeight;

// Scene setup
const scene = new THREE.Scene();
scene.background = new THREE.Color(0xf0f0f0);

// Camera setup
const camera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000);
camera.position.z = 5;

// Renderer setup
const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setSize(width, height);
renderer.shadowMap.enabled = true;
viewer.appendChild(renderer.domElement);

// Controls setup
const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;
controls.dampingFactor = 0.05;

// Lights setup
const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);

const directionalLight = new THREE.DirectionalLight(0xffffff, 1);
directionalLight.position.set(5, 5, 5);
directionalLight.castShadow = true;
scene.add(directionalLight);

const pointLight = new THREE.PointLight(0xffffff, 1);
pointLight.position.set(-5, 5, -5);
pointLight.castShadow = true;
scene.add(pointLight);

// Ground plane
const groundGeometry = new THREE.PlaneGeometry(10, 10);
const groundMaterial = new THREE.MeshStandardMaterial({ 
    color: 0xcccccc,
    side: THREE.DoubleSide
});
const ground = new THREE.Mesh(groundGeometry, groundMaterial);
ground.rotation.x = -Math.PI / 2;
ground.receiveShadow = true;
scene.add(ground);

// Background plane
const bgGeometry = new THREE.PlaneGeometry(10, 10);
const bgMaterial = new THREE.MeshBasicMaterial({ 
    color: 0x000000,
    side: THREE.DoubleSide
});
const background = new THREE.Mesh(bgGeometry, bgMaterial);
background.position.z = -5;
scene.add(background);

// Example objects
const cubeGeometry = new THREE.BoxGeometry(1, 1, 1);
const cubeMaterial = new THREE.MeshStandardMaterial({ color: 0x00ff00 });
const cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
cube.position.set(-2, 0.5, 0);
cube.castShadow = true;
scene.add(cube);

// Pyramid using BufferGeometry
const pyramidGeometry = new THREE.BufferGeometry();
const pyramidVertices = new Float32Array([
    0, 1, 0,    // top
    -1, -1, 1,  // front left
    1, -1, 1,   // front right
    1, -1, -1,  // back right
    -1, -1, -1  // back left
]);
const pyramidIndices = [
    0, 1, 2,    // front face
    0, 2, 3,    // right face
    0, 3, 4,    // back face
    0, 4, 1,    // left face
    1, 4, 3,    // bottom face 1
    1, 3, 2     // bottom face 2
];
pyramidGeometry.setAttribute('position', new THREE.BufferAttribute(pyramidVertices, 3));
pyramidGeometry.setIndex(pyramidIndices);
pyramidGeometry.computeVertexNormals();

const pyramidMaterial = new THREE.MeshStandardMaterial({ color: 0xff0000 });
const pyramid = new THREE.Mesh(pyramidGeometry, pyramidMaterial);
pyramid.position.set(2, 0.5, 0);
pyramid.castShadow = true;
scene.add(pyramid);

// Animation loop
function animate() {
    requestAnimationFrame(animate);
    controls.update();
    renderer.render(scene, camera);
}
animate();

// Window resize handler
window.addEventListener('resize', () => {
    const width = viewer.clientWidth;
    const height = viewer.clientHeight;
    camera.aspect = width / height;
    camera.updateProjectionMatrix();
    renderer.setSize(width, height);
});

// Light controls
document.getElementById('ambient-light').addEventListener('change', (e) => {
    ambientLight.visible = e.target.checked;
});

document.getElementById('directional-light').addEventListener('change', (e) => {
    directionalLight.visible = e.target.checked;
});

document.getElementById('point-light').addEventListener('change', (e) => {
    pointLight.visible = e.target.checked;
});

// Color control
document.getElementById('model-color').addEventListener('input', (e) => {
    const color = new THREE.Color(e.target.value);
    if (currentSTLModel) {
        currentSTLModel.material.color = color;
    }
});

// STL Loader
const loader = new STLLoader();

// Load STL model
async function loadSTLModel(url) {
    try {
        const geometry = await loader.loadAsync(url);
        const material = new THREE.MeshStandardMaterial({ 
            color: document.getElementById('model-color').value,
            metalness: 0.5,
            roughness: 0.5
        });
        const mesh = new THREE.Mesh(geometry, material);

        // Центрируем и масштабируем модель
        geometry.computeBoundingBox();
        const box = geometry.boundingBox;
        const center = box.getCenter(new THREE.Vector3());
        const size = box.getSize(new THREE.Vector3());
        const maxDim = Math.max(size.x, size.y, size.z);
        const scale = 2 / maxDim;
        mesh.scale.set(scale, scale, scale);
        mesh.position.sub(center.multiplyScalar(scale));
        mesh.castShadow = true;

        // Удаляем все объекты, кроме источников света
        scene.children = scene.children.filter(obj => obj.type.includes('Light'));
        scene.add(mesh);

        // Сохраняем ссылку на текущую STL-модель
        currentSTLModel = mesh;

        // Сброс позиции камеры
        camera.position.set(0, 2, 5);
        controls.reset();
    } catch (error) {
        console.error('Error loading STL model:', error);
    }
}

// Модифицируем loadModels для добавления кнопки "Просмотреть"
async function loadModels(page = 1) {
    try {
        const response = await fetch(`/models?page=${page}`);
        const data = await response.json();
        
        modelsContainer.innerHTML = '';
        
        if (data.models.length === 0) {
            modelsContainer.innerHTML = '<div class="no-models">No models found</div>';
            return;
        }
        
        data.models.forEach(model => {
            const modelCard = document.createElement('div');
            modelCard.className = 'model-card';
            modelCard.innerHTML = `
                <h3>${model.name}</h3>
                <p class="description">${model.description || 'No description'}</p>
                <div class="meta">
                    <p><strong>Author:</strong> ${model.author_name}</p>
                    <p><strong>Uploaded:</strong> ${formatDate(model.created_at)}</p>
                </div>
                <button class="view-btn" data-model-url="${model.file_path}">View Model</button>
                <a href="${model.file_path}" class="download-btn" download>Download Model</a>
            `;
            modelsContainer.appendChild(modelCard);
        });

        // Add event listeners to view buttons
        document.querySelectorAll('.view-btn').forEach(btn => {
            btn.addEventListener('click', () => {
                const modelUrl = btn.dataset.modelUrl;
                loadSTLModel(modelUrl);
            });
        });

        currentPage = data.pagination.currentPage;
        pageInfo.textContent = `Page ${currentPage} of ${data.pagination.totalPages}`;
        prevPageBtn.disabled = !data.pagination.hasPrev;
        nextPageBtn.disabled = !data.pagination.hasNext;
    } catch (error) {
        console.error('Error loading models:', error);
        modelsContainer.innerHTML = '<div class="error">Error loading models. Please try again later.</div>';
    }
}

// Event Listeners
loginBtn.addEventListener('click', () => showAuthForm('login'));
registerBtn.addEventListener('click', () => showAuthForm('register'));
logoutBtn.addEventListener('click', async () => {
  try {
    const response = await fetch('/logout', { method: 'POST' });
    const data = await response.json();
    if (response.ok && data.success) {
      isAuthenticated = false;
      updateAuthUI();
      window.location.href = data.redirect;
    }
  } catch (error) {
    console.error('Error logging out:', error);
  }
});

uploadBtn.addEventListener('click', () => {
  window.location.href = '/models/upload';
});

loginFormElement.addEventListener('submit', async (e) => {
  e.preventDefault();
  const formData = new FormData(loginFormElement);
  
  try {
    const response = await fetch('/login', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        username: formData.get('username'),
        password: formData.get('password'),
      }),
    });

    const data = await response.json();
    if (response.ok && data.success) {
      isAuthenticated = true;
      updateAuthUI();
      window.location.href = data.redirect;
    } else {
      alert(data.error || 'Login failed');
    }
  } catch (error) {
    console.error('Error logging in:', error);
    alert('Login failed');
  }
});

registerFormElement.addEventListener('submit', async (e) => {
  e.preventDefault();
  const formData = new FormData(registerFormElement);
  
  try {
    const response = await fetch('/register', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        username: formData.get('username'),
        password: formData.get('password'),
      }),
    });

    const data = await response.json();
    if (response.ok && data.success) {
      isAuthenticated = true;
      updateAuthUI();
      window.location.href = data.redirect;
    } else {
      alert(data.error || 'Registration failed');
    }
  } catch (error) {
    console.error('Error registering:', error);
    alert('Registration failed');
  }
});

prevPageBtn.addEventListener('click', () => {
  if (currentPage > 1) {
    loadModels(currentPage - 1);
  }
});

nextPageBtn.addEventListener('click', () => {
  loadModels(currentPage + 1);
});

// Initialize
checkAuth();
loadModels(1); 