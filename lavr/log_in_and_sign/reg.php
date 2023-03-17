<?php
    session_start();
    mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
    $login=$_POST['login'];
    $pass=$_POST['pass'];
    $name=$_POST['name'];
    $date_b=$_POST['date_b'];
    $pass_n=$_POST['pass_n'];
    $tel=$_POST['tel'];

    if(($login=='')||($pass=='')||($name=='')||($date_b=='')||($pass_n=='')||($tel=='')){
        $_SESSION['Message_pass'] = "Все поля должны быть заполнены";
        header('Location: sign.php');
        exit();
    }
    if (strlen($pass) < 8) {
        $_SESSION['Message_pass'] = "Пароль слишком короткий";
        header('Location: sign.php');
        exit();
    }

    if (!preg_match("#[0-9]+#", $pass)) {
        $_SESSION['Message_pass']= "Пароль должен содержать цифры";
        header('Location: sign.php');
        exit();
    }

    if (!preg_match("#[a-zA-Z]+#", $pass)) {
        $_SESSION['Message_pass'] = "Пароль должен содержать буквы";
        header('Location: sign.php');
        exit();
    }     
    if($pass!=$pass_n){
        $_SESSION['Message_pass']='Пароли не совпадают';
        header('Location: sign.php');
        exit();
    }
    //var_dump($login,$pass,$name,$date_b,$tel);

    $hash = md5($pass);
    $query="INSERT INTO `USER`(`Name`, `date_birth`, `login`, `password`, `tel`) 
    VALUES ('$name','$date_b','$login','$hash','$tel')";
    $check_login="SELECT * FROM USER WHERE login = '$login'";
    $mysql=new mysqli('localhost','root','root','MY_DATA');
    $check=$mysql->query($check_login);
    $log=$check->fetch_assoc();
    if ($log['Name']!=''){
        $_SESSION['Message_login']='Логин занят';
        header('Location: sign.php');
        exit();
    }
    $mysql->query($query);
    $check=$mysql->query($check_login);
    $log=$check->fetch_assoc();
    if ($log['Name']!=''){
        setcookie('user_id',$log['user_id'],time()+3600*24*30,"/");
        header('Location: ../account/account.php');
        exit();
    }
    $mysql->close();
    header('Location: sign.php'); 
?>