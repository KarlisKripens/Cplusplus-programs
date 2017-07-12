$(document).ready(function()
{


});
function isset(variable)
{
    //Funkcija ir analogs PHP funkcijai isset(). Funkcija pārbauda, vai padotais mainīgais ir definēts.
    if(variable === null) return false;
    if(variable === "") return false;
    else return true;
}
function validate_Login()
{
    var user_Key = $('#the_key').val();
    if(!isset(user_Key)) alert("Ievadi tak paroli -.-")
    else
    {
        $.post( "../functions.php", { func: 'validate_user',  user_Key: user_Key}, function(response)
        {
            var Data = $.parseJSON(response);
            console.log(Data);
            if(Data == 0) alert("Nepareiza parole.");
            else if (Data == 1)
            {
                window.location.href = "../index.php";
            }
        });
    }
    return 0;
}
