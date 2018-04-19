window.onload = function() {
        
    var allInputs = document.getElementsByTagName('input');
    
    for(var i = 0; i < allInputs.length; i++) {
        
        if(allInputs[i].type == 'checkbox' && allInputs[i].name.includes('[Select Course][' + allInputs[i].value + '-All' + ']')) {
            
            allInputs[i].setAttribute('onclick', 'checkUncheckAll(this, "' + allInputs[i].value + '");');
            
        }
        
    }
    
}

function checkUncheckAll(theElement, course) {
    
    var theForm = theElement.form, z = 0;
      
    for(z=0; z < theForm.length; z++){
          
        if(theForm[z].type == 'checkbox' && theForm[z].name.includes('courses')) {

            theForm[z].checked = theElement.checked; 

        }
        
    }
      
}
