<?php
    try{
        $db=new PDO('mysql:host=localhost;dbname=practica','root','root');
        session_start();
        $form=$_POST;
            if(($form['name']!=NULL)&($form['email']!=NULL)){
            $file = 'review/review.txt';
            $string="\nПользователь: ".$form['name']."\n"."Почта: ".$form['email']."\n"."Оценка: ".$form['estimation']."\n"."Отзыв\n".$form['review'];
            $path = "img/".$_FILES['img']['name'];
                if (!preg_match('/[A-Za-zА-Яа-яЁё]+(\s+[A-Za-zА-Яа-яЁё]+)?/', $form['name'])){
                    $errors['name'] = 'should consist of two words!';
                    exit;
                }
                
                if (filter_var($form['email'], FILTER_VALIDATE_EMAIL) != $form['email']){
                    $errors['email'] = 'provide correct email!';
                    exit;
                }
                
            var_dump($errors);
            file_put_contents($file, $string, FILE_APPEND | LOCK_EX);
            move_uploaded_file($_FILES['img']['tmp_name'],$path);
            $today = date("Y-n-j"); 
            $query="INSERT INTO `reviews`( `email`, `name`, `date_insert`, `rate`, `text`, `image_path`) VALUES ('".$form['email']."','".$form['name']."','$today','".$form['estimation']."','".$form['review']."','$path')";
            $db->query($query);
        }
        else{
            $_SESSION['Message_no_full_data'] = "Поля имя и адрес элекстронной почты должны быть заполнены!";
            header('Location: index.php');
        }
        $query='SELECT * FROM `reviews`';
        $result=$db->query($query);
        while($row=$result->fetch(PDO::FETCH_ASSOC)){
            echo "<p>Пользователь:".$row['name']." ".$row['email']." <br> Оценка:".$row['rate']." <br> Отзыв: <br>".$row['text']."<br> ".$row['date_insert']."<br></p>";
        }
        $db=null;
        // $query='SELECT * FROM `reviews`';
        // $result=$db->query($query);
        // $count=$result->fetchALL();
        // var_dump($count);
    }
    catch(PDOException $e){
        die($e->getMessage());
    }
?>
