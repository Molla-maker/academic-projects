// Form validation
document.addEventListener('DOMContentLoaded', () => {
  const forms = document.querySelectorAll('form[novalidate]');
  
  forms.forEach(form => {
    const inputs = form.querySelectorAll('input, textarea');
    
    inputs.forEach(input => {
      // Add validation on input
      input.addEventListener('input', () => {
        validateInput(input);
      });
      
      // Add validation on blur
      input.addEventListener('blur', () => {
        validateInput(input);
      });
    });
    
    // Add validation on submit
    form.addEventListener('submit', (e) => {
      let isValid = true;
      
      inputs.forEach(input => {
        if (!validateInput(input)) {
          isValid = false;
        }
      });
      
      if (!isValid) {
        e.preventDefault();
      }
    });
  });
});

function validateInput(input) {
  const value = input.value.trim();
  let isValid = true;
  let errorMessage = '';
  
  // Remove existing error message
  const existingError = input.parentElement.querySelector('.error-message');
  if (existingError) {
    existingError.remove();
  }
  
  // Remove error class
  input.classList.remove('error');
  
  // Required field validation
  if (input.hasAttribute('required') && !value) {
    isValid = false;
    errorMessage = 'This field is required';
  }
  
  // Text length validation for name
  if (input.id === 'name' && value.length > 0) {
    if (value.length < 3) {
      isValid = false;
      errorMessage = 'Name must be at least 3 characters long';
    } else if (value.length > 100) {
      isValid = false;
      errorMessage = 'Name must be less than 100 characters';
    }
  }
  
  // Description length validation
  if (input.id === 'description' && value.length > 0) {
    if (value.length > 500) {
      isValid = false;
      errorMessage = 'Description must be less than 500 characters';
    }
  }
  
  // File type validation for model upload
  if (input.type === 'file' && input.accept) {
    const file = input.files[0];
    if (file) {
      const acceptedTypes = input.accept.split(',').map(type => type.trim());
      const fileExtension = file.name.split('.').pop().toLowerCase();
      
      if (!acceptedTypes.includes(`.${fileExtension}`)) {
        isValid = false;
        errorMessage = `Only ${acceptedTypes.join(', ')} files are allowed`;
      }
      
      // File size validation (10MB limit)
      if (file.size > 10 * 1024 * 1024) {
        isValid = false;
        errorMessage = 'File size must be less than 10MB';
      }
    }
  }
  
  // Show error if validation failed
  if (!isValid) {
    input.classList.add('error');
    const errorElement = document.createElement('div');
    errorElement.className = 'error-message';
    errorElement.textContent = errorMessage;
    input.parentElement.appendChild(errorElement);
  }
  
  return isValid;
} 