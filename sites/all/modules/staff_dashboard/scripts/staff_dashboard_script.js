window.onload = function() {
    
    var allBoxes = document.querySelectorAll('#rooms td select.form-control.form-select');

    for(var i = 0; i < allBoxes.length; i++)
        allBoxes[i].style.display = 'none';
    
}

function collapse($id) {
    
    $id = "edit-rooms-" + $id + "-select-course";
    
    var checkbox = document.getElementById($id);
    
    if(checkbox.style.display == 'none') 
        checkbox.style.display = 'block';

    else
        checkbox.style.display = 'none';
    
}