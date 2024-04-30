import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterOutlet } from '@angular/router';
import { DefaultService } from '../client';
import { HttpClientModule } from '@angular/common/http';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [CommonModule, RouterOutlet,HttpClientModule],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css',
  providers:[DefaultService],
})
export class AppComponent {
  title = 'frontend';
  constructor(private service: DefaultService){}
  getItems() {
    this.service.getItemsApiItemsGet().subscribe(o=>{
      alert(JSON.stringify(o));
    })
  }
  postItems() {
    this.service.createItemApiItemsPost({requestBody:{name:'123',price:234}}).subscribe(o=>{
      alert(JSON.stringify(o));
    })
  }
}
