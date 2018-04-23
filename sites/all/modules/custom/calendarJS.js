window.onload = function() {
    
    let colors = ["#B22222", "Blue", "#1F5F7A", "#556B2F", "Red", "#CD5C5C", "Brown", "Black","#BDB76B", "#696969", "DarkGoldenRod", "DarkOrchid","DarkOrange", "#CD853F", "Green"];
   // let colors = ["DeepPink", "Blue", "Chartreuse", "Red", "Aqua", "Brown", "Aquamarine", "Black", "Cyan", "DarkGoldenRod", "DarkOrchid","DarkOrange", "Gold", "Green", "GreenYellow"];
    let courses = ['NURS2004', 'NURS2009', 'NURS2011', 'NURS2013', 'NURS3009', 'NURS3010', 'NURS3011', 'NURS3028', 'NURS3029', 'NURS3030', 'NURS4000', 'NURS4001', 'NURS4002', 'NURS4066', 'NURS4067'];

    let x = document.getElementsByClassName("views-field views-field-field-course-names");
    let eventBorder = document.getElementsByClassName("calendar monthview");
    let output;
    for (output = 0; output < x.length; output++) {
        x[output].style.color = "blue";
        var htmlString = x[output].innerHTML;
        var courseName = htmlString.substring(htmlString.lastIndexOf("content\">")+9,htmlString.lastIndexOf("<"));
        if (checkValue(courseName, courses) === 'Exist')
        {
            x[output].style.color = colors[courses.indexOf(courseName)];
            eventBorder[output].style.borderLeft = "4px solid " + colors[courses.indexOf(courseName)];

        }
    }
};
function checkValue(value,arr){
    var status = 'Not exist';

    for(var i=0; i<arr.length; i++){
        var name = arr[i];
        if(name === value){
            status = 'Exist';
            break;
        }
    }

    return status;
}

